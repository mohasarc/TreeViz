import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import Badge from 'react-bootstrap/Badge'
import Button from 'react-bootstrap/Button'
import { withStyles, makeStyles } from '@material-ui/core/styles';
import Slider from '@material-ui/core/Slider';
import p5 from 'p5'

/**
 * The canvas component
 */
class Canvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            height : 900,
            width : 100,
            canvasNo : props.canvasNo,
            treeType : props.treeType,
            canvasRef : React.createRef(),
            tree : props.tree,
            myP5 : null,
            updateTreeOperations : props.updateTreeOperations,

        }
        this.node = props.theNode;
        this.state.myP5 = this.props.p5;
        this.state.height = this.state.tree.getHeight();
        this.update = this.update.bind(this);
        this.dragged = this.dragged.bind(this);
        this.pressed = this.pressed.bind(this);
        this.released = this.released.bind(this);
        this.popTree = this.popTree.bind(this);
        this.copyTreeString = this.copyTreeString.bind(this);
        this.treeToCenter = this.treeToCenter.bind(this);
        this.handleZoom = this.handleZoom.bind(this);
        this.popTreeEnable = true;
        this.isCalled = false;
    }

    update(){
        // console.log('update called with tree', this.state.tree);
        console.log('update called');
        this.state.myP5.windowResized(this.state.width, this.state.tree.getHeight());
        this.setState((prevState) => {
            return {
                width : prevState.canvasRef.current.offsetWidth
            }
        });
    }

    componentDidMount() {
        window.document.getElementById(this.state.canvasNo).appendChild(this.node);
        var newWidth = this.state.canvasRef.current.offsetWidth;
        this.state.myP5.width = this.state.width;
        this.state.myP5.height = this.state.height;
        this.state.myP5.tree = this.state.tree;
        this.state.myP5.tree.center(newWidth);
        this.setState({
            height : this.state.tree.getHeight() + 40,
            width : newWidth
        });

        this.state.myP5.windowResized(newWidth, this.state.tree.getHeight());
        window.addEventListener("resize", this.update);
        window.addEventListener("orientationchange", ()=>{setTimeout(this.update, 20)}, false);
    }

    pressed(e){
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
        } else {
            this.initialX = e.clientX;
            this.initialY = e.clientY;
        }
    }

    released(e){
        this.mousePressed = false;
    }

    dragged(e){
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

    popTree(e){
        if (this.props.topTree){
            this.props.popTree();
        } else {
            this.popTreeEnable = false;
        }

        e.preventDefault();
    }

    copyTreeString(e){
        this.state.updateTreeOperations(this.state.tree.getTreeString());
        e.preventDefault();
    }

    treeToCenter(e){
        this.setState(prevState=>{
            if (!this.isCalled){
                prevState.tree.center(prevState.width);
                this.isCalled = true;
            } else {
                this.isCalled = false;
            }
        });
        e.preventDefault();
    }

    handleZoom(e, value){
        // console.log(value);
        // this.state.myP5.scaleValue = value/50;
        if (e.ctrlKey){
            e.preventDefault();
            this.state.tree.setScale(this.state.tree.getScale() - e.deltaY * 0.05);
        }

    }

    render(){
        return  (
        <Container>
            <Container className='canvas' style={{'height' : this.state.height }}>
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
                    <Col xs={4} md={4} lg={4}>
                        <div className='float-left'>
                            <Badge variant='warning'>
                                {this.state.treeType}
                            </Badge>
                        </div>
                    </Col>
                    <Col xs={2} md={2} lg={2}>
                        <Canvasno no={this.state.canvasNo}/>
                    </Col>
                    <Col xs={5} md={5} lg={5}>
                        <div className='float-right'>
                            <a href='#' className='badge badge-light'  onClick={this.treeToCenter}
                               style={{'margin-right':'0.2em', 'margin-bottom':'0.3em'}}>
                                <div className='center' >.</div>
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
                        <div id={this.state.canvasNo} onTouchStart={this.pressed} onMouseDown={this.pressed} 
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

export default Canvas;