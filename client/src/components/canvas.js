import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import Badge from 'react-bootstrap/Badge'
import { withSnackbar } from 'notistack';

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
        }

        this.node = props.theNode;
        this.popTreeEnable = true;
        this.isCalled = false;
        this.disableScrolling = true;
    }

    componentDidMount() {
        window.document.getElementById(this.state.canvasNo).appendChild(this.node);
        var canvasWidth = this.state.canvasRef.current.offsetWidth;
        this.state.myP5.tree = this.state.tree; // put a reference to the tree into p5 object
        this.state.myP5.windowResized(canvasWidth, this.state.tree.getHeight());

        this.state.tree.setCenterX(canvasWidth/2);
        this.state.tree.setCenterY(40);
        this.state.tree.center();

        window.addEventListener("resize", this.resize);      
        window.addEventListener("orientationchange", ()=>{setTimeout(this.resize, 20)}, false);
        window.addEventListener('touchmove', (e)=>{if(!this.disableScrolling){e.preventDefault()}}, false);

        this.setState({
            height : this.state.tree.getHeight() + 40,
        });
    }

    resize = () => {
        if (this.state.canvasRef.current){
            var canvasWidth = this.state.canvasRef.current.offsetWidth;
            this.state.myP5.windowResized(canvasWidth, this.state.tree.getHeight());
            this.setState({'height' : this.state.tree.getHeight() + 40});
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
        
        e.preventDefault();
    }

    dragged = (e) => {
        e.preventDefault();

        if (this.mousePressed){
            // update initial values
            if (e.touches){
                this.state.tree.moveTree(e.changedTouches[0].clientX - this.initialX, 
                                         e.changedTouches[0].clientY - this.initialY);
                this.initialX = e.touches[0].clientX;
                this.initialY = e.touches[0].clientY;
            } else {
                this.state.tree.moveTree(e.clientX - this.initialX, e.clientY - this.initialY);
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
        this.state.tree.setCenterX(this.state.canvasRef.current.offsetWidth/2);
        this.state.tree.setCenterY(40);
        this.state.tree.setScale(1);
        this.state.tree.center();
        this.resize();
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
            var canvasWidth = this.state.canvasRef.current.offsetWidth;
            this.state.tree.setCenterX(this.state.tree.getCenterX() - (e.clientX - rect.left - this.state.tree.getCenterX()) * e.deltaY * - 0.05 * (1/this.state.tree.scale));
            // this.state.tree.setCenterY(this.state.tree.getCenterY() - (e.clientY - rect.top - this.state.tree.getCenterY()) * e.deltaY * - 0.05);
            this.state.tree.setScale(this.state.tree.getScale() - e.deltaY * 0.05 * this.state.tree.getScale());
            this.state.tree.center();
            this.state.myP5.windowResized(canvasWidth, this.state.tree.getHeight());
            this.setState({'height' : this.state.tree.getHeight() + 40});

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
                if (steps[i].text != ''){}
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
                setTimeout(loop.bind(this), delay * immediatly);  // call myself in 1 seconds time if required
            }
        }.bind(this))(); // above function expression is called immediately to start it off

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
            this.resize(); // in case original tree is larger
            e.preventDefault();
        }
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

// export default Canvas;
export default withSnackbar(Canvas);