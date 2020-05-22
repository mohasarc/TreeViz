import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import Badge from 'react-bootstrap/Badge'
import Button from 'react-bootstrap/Button'
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
            myRef : React.createRef(),
            tree : props.tree,
            myP5 : null,
            updateTreeOperations : props.updateTreeOperations,

        }
        this.state.height = this.state.tree.getHeight();
        this.update = this.update.bind(this);
        this.dragged = this.dragged.bind(this);
        this.pressed = this.pressed.bind(this);
        this.released = this.released.bind(this);
        this.popTree = this.popTree.bind(this);
        this.copyTreeString = this.copyTreeString.bind(this);
        this.popTreeEnable = true;
    }

    // P5
    Sketch = (p) => {
        p.setup = () => {
            p.createCanvas(this.state.width, this.state.height - 40);
        }
   
        p.draw = () => {
            p.background('#34495e');
            this.state.tree.draw(p, this.state.width);
        }

        p.windowResized = (width, height) => {
            this.state.tree.resize(width);
            p.resizeCanvas(width, height);
            p.redraw();
        }
    }

    update(){
        // console.log('update called with tree', this.state.tree);
        this.state.myP5.windowResized(this.state.width, this.state.tree.getHeight());
        this.setState((prevState) => {
            return {
                width : prevState.myRef.current.offsetWidth
            }
        });
    }

    componentDidMount() {
        var newWidth = this.state.myRef.current.offsetWidth;
        this.state.myP5 = new p5(this.Sketch, this.state.myRef.current);
        // console.log('conponent did mound', newWidth);
        this.setState({
            height : this.state.tree.getHeight() + 40,
            width : newWidth
        });

        this.state.myP5.windowResized(newWidth, this.state.tree.getHeight());
        window.addEventListener("resize", this.update);
    }

    pressed(e){
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
            // console.log('touch event');
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
                this.state.tree.moveTree(e.changedTouches[0].clientX - this.initialX, e.changedTouches[0].clientY - this.initialY);
                this.initialX = e.touches[0].clientX;
                this.initialY = e.touches[0].clientY;
                // console.log('touch event');
            } else {
                this.state.tree.moveTree(e.clientX - this.initialX, e.clientY - this.initialY);
                this.initialX = e.clientX;
                this.initialY = e.clientY;
            }
        }
        // console.log('mouse not pressed but moving', e.clientX, e.clientY);
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
    
    render(){
        return  (
        <Container>
            <Container className='canvas' style={{'height' : this.state.height }}>
                <Row xs={12} md={12} lg={12} noGutters={true} className='justify-content-xs-left'>
                    <Col xs={1} md={1} lg={1}>
                        {
                            this.props.topTree?(
                                <a  href="#" onClick={this.popTree} className='badge badge-warning' style={{'border-radius' : '100%', 'background-color':'white'}}>X</a>
                            ):<div/>
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
                        <Canvasno no={this.state.canvasNo}></Canvasno>
                    </Col>
                    <Col xs={5} md={5} lg={5}>
                        <div className='float-right'>
                            <a  href="#" onClick={this.copyTreeString} className='badge badge-secondary'>Copy tree string</a>
                        </div>
                    </Col>
                </Row>
                <Row xs={1} md={1} lg={1} noGutters={true}>
                    <Col key={this.state.tree.getId()}>
                        <div onTouchStart={this.pressed} onMouseDown={this.pressed} 
                             onTouchMove={this.dragged} onMouseMove={this.dragged} 
                             onTouchEnd={this.released} onMouseUp={this.released} ref={this.state.myRef} />
                    </Col>
                </Row>
            </Container>
        </Container>
        );
    }
}

export default Canvas;