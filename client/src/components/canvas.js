import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import Badge from 'react-bootstrap/Badge'
import { withSnackbar } from 'notistack';
import { Slider } from 'rsuite';
import 'rsuite/dist/styles/rsuite-default.css';

/**
 * The canvas component
 */
class Canvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            height : props.tree.getHeight(),
            width : 100,
            canvasNo : props.canvasNo,
            treeType : props.treeType,
            canvasRef : React.createRef(),
            tree : props.tree,
            myP5 : this.props.p5,
            updateTreeOperations : props.updateTreeOperations,
            speed : 1500,
        }

        this.node = props.theNode;
        this.popTreeEnable = true;
        this.isCalled = false;
        this.disableScrolling = true;
    }

    componentDidMount() {
        window.document.getElementById(this.state.canvasNo).appendChild(this.node);
        var canvasWidth = this.state.canvasRef.current.offsetWidth;
        var canvasHeight = this.state.tree.getHeight() + 0.4 * this.state.tree.getHeight();
        let initY = (canvasHeight + 80 - this.state.tree.getHeight()) / 2;

        // add the tree to p5 object
        this.state.myP5.setTree(this.state.tree);
        this.state.myP5.windowResized(canvasWidth, canvasHeight + 25);
        this.state.myP5.moveCamera(this.state.tree.tx ? this.state.tree.tx : canvasWidth/2, this.state.ty ? this.state.ty : initY);

        window.addEventListener("resize", this.resize);      
        window.addEventListener("orientationchange", ()=>{setTimeout(this.resize, 20)}, false);
        window.addEventListener('touchmove', (e)=>{if(!this.disableScrolling){e.preventDefault()}}, false);

        this.setState({
            height : canvasHeight + 80,
        });

        // auto play steps
        if (this.state.tree.isNewlyAdded()){
            this.state.tree.setNewlyAdded(false);
            this.playSteps();
        }
    }

    resize = () => {
        if (this.state.canvasRef.current){
            var canvasWidth = this.state.canvasRef.current.offsetWidth;
            this.state.myP5.windowResized(canvasWidth, this.state.tree.getHeight() + 0.4 * this.state.tree.getHeight() + 25);
            this.setState({'height' : this.state.tree.getHeight() + 0.4 * this.state.tree.getHeight() + 80});
        }
    }

    pressed = (e) => {
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
        } else {
            this.initialX = e.clientX;
            this.initialY = e.clientY;
        }

        e.preventDefault();
    }

    released = (e) => {
        this.mousePressed = false;
        document.body.style.overflow = "scroll";
        
        e.preventDefault();
    }

    dragged = (e) => {
        e.preventDefault();
        if (this.mousePressed){
            // update initial values
            if (e.touches){
                document.body.style.overflow = "hidden";
                this.state.myP5.moveCamera((e.touches[0].clientX - this.initialX) * 0.5, (e.touches[0].clientY - this.initialY) * 0.5);

                this.initialX = e.touches[0].clientX;
                this.initialY = e.touches[0].clientY;
            } else {
                this.state.myP5.moveCamera((e.clientX - this.initialX) * 0.5, (e.clientY - this.initialY) * 0.5);

                this.initialX = e.clientX;
                this.initialY = e.clientY;
            }
        }
    }

    popTree = (e) => {
        if (this.props.topTree){
            this.props.popTree(this.state.tree.getId());
        } else {
            this.popTreeEnable = false;
        }

        e.preventDefault();
    }

    copyTreeString = (e) => {
        if (this.state.updateTreeOperations){
            var treeDescription;
            if (this.state.tree.getTreeSequence() == '')
                treeDescription = this.state.tree.getTreeString();
            else
                treeDescription = this.state.tree.getTreeString() + ":" + this.state.tree.getTreeSequence();
            this.state.updateTreeOperations(treeDescription);
        }
        e.preventDefault();
    }

    treeToCenter = (e) => {
        let initY = (this.state.height - this.state.tree.getHeight()) / 2;
        this.state.myP5.moveCamera((this.state.canvasRef.current.offsetWidth/2) - this.state.myP5.tree.tx, initY - this.state.myP5.tree.ty);
        this.state.tree.setScale(1);
        e.preventDefault();
    }

    treeDetach = (e) => {
        // opening a new window
        var popup = window.open('./fullTreeView');

        // sending a message for the new window
        var interval = setInterval(() => {
            if (popup.document.readyState == 'complete'){
                console.log('sending', this.state.tree);
                popup.postMessage({'tree':this.state.tree}, window.location.href);
                clearInterval(interval);
            }
        }, 300);

        e.preventDefault();
    }

    saveAsImage = (e) => {
        this.state.myP5.createImage();
        e.preventDefault();
    }

    handleZoom = (e, value) => {
        if (e.ctrlKey){
            let rect = this.state.canvasRef.current.getBoundingClientRect();
            this.state.myP5.zoom(e.deltaY < 0 ? 1.05 : 0.95, e.clientX - rect.left, e.clientY - rect.top);
            e.preventDefault();
        }
    }

    playSteps = (e) => {
        var i = 0;
        var immediatly = 1;
        this.state.tree.beingEnimated = true;
        var steps = this.state.tree.getSteps();
        var delay = 1500;

        (function loop() {
            if (!this.state.tree.beingEnimated){
                i = steps.length; // skip ahead to the last step
                immediatly = 0; // To stop immedietly without delay
            }

            // If steps were not empty
            if (i < steps.length){
                if (steps[i].text != '')
                    this.props.enqueueSnackbar(steps[i].text);

                if (steps[i].treeStr != ''){
                    this.state.tree.construct(steps[i].treeStr);
                    this.state.tree.setNote(steps[i].note);
                }

                // center needs to be called twice
                this.state.tree.center();
                this.state.tree.center();
                this.resize(); // in case tree in step i is larger
            }

            if (i == steps.length - 1)
                this.stopSteps();

            if (++i < steps.length) {
                setTimeout(loop.bind(this), this.state.speed * immediatly);  // call myself in 1 seconds time if required
            }
        }.bind(this))(); // above function expression is called immediately to start it off

        if (e)
            e.preventDefault();
    }

    stopSteps = (e) => {
        this.state.tree.beingEnimated = false;

        if (e){
            var steps = this.state.tree.getSteps();
            this.state.tree.construct(steps[steps.length - 1].treeStr);
            this.state.tree.setNote('');

            // center needs to be called twice
            this.state.tree.center();
            this.state.tree.center();
            e.preventDefault();
        }
        this.resize(); // in case original tree is larger
    }

    handleSlider = (value) => {
        // this.setState({speed : Number(e.target.value)});
        console.log(value);
        value = 3000 - ( value / 100 * 3000 );
        this.state.speed = value;
    }
    

    render(){
        return  (
        <Container>
            <Container className='canvas' style={{'height' : this.state.height}}>
                <Row xs={12} md={12} lg={12} noGutters={true} className='justify-content-xs-left'>
                    <Col xs={1} md={1} lg={1}>
                        {
                            this.props.topTree
                            ?<a  href="#" onClick={this.popTree} 
                                className='badge badge-light' 
                                style={{'border-radius' : '100%'}}>
                                X
                            </a>
                            :<div/>
                        }
                    </Col>
                    <Col xs={3} md={4} lg={4}>
                        <div className='float-left'>
                            <Badge variant='warning'>
                                {this.state.treeType}
                            </Badge>
                        </div>
                    </Col>
                    <Col xs={2} md={2} lg={2}>
                        <Canvasno no={this.state.canvasNo}/>
                    </Col>
                    <Col xs={6} md={5} lg={5}>
                        <div className='float-right'>
                            <a href='#' className='badge badge-light'  
                            onClick={!this.state.tree.beingEnimated?this.playSteps:this.stopSteps}
                            style={{'margin-right':'0.2em', 'margin-bottom':'0.3em'}}>
                            <div className={!this.state.tree.beingEnimated?'play':'stop'} style={{'color' : '#FFFFFF'}}>.</div>
                            </a>

                            <a href='#' className='badge badge-light'  onClick={this.saveAsImage}
                               style={{'margin-right':'0.2em', 'margin-bottom':'0.3em'}}>
                                <div className='save' >.</div>
                            </a>
                            <a href='#' className='badge badge-light'  onClick={this.treeDetach}
                               style={{'margin-right':'0.2em', 'margin-bottom':'0.3em'}}>
                                <div className='detach' style={{'color' : '#FFFFFF'}} >.</div>
                            </a>
                            <a href='#' className='badge badge-light'  onClick={this.treeToCenter}
                               style={{'margin-right':'0.2em', 'margin-bottom':'0.3em'}}>
                                <div className='center' style={{'color' : '#FFFFFF'}} >.</div>
                            </a>
                            <a  href="#" onClick={this.copyTreeString} 
                                className='badge badge-secondary'>
                                USE
                            </a>
                        </div>
                    </Col>
                </Row>
                <Row>
                    <Col>
                        <Slider defaultValue={50} style={{'margin-bottom' : '0.5em', 'margin-top' : '0.5em'}} onChange={this.handleSlider}/>
                    </Col>
                </Row>
                <Row xs={1} md={1} lg={1} noGutters={true}>
                    <Col>
                        <div id={this.state.canvasNo} 
                             onTouchStart={this.pressed} onMouseDown={this.pressed} 
                             onTouchMove={this.dragged} onMouseMove={this.dragged} 
                             onTouchEnd={this.released} onMouseUp={this.released} 
                             ref={this.state.canvasRef} onWheel={this.handleZoom}
                        />
                    </Col>
                </Row>
            </Container>
        </Container>
        );
    }
}

export default withSnackbar(Canvas);