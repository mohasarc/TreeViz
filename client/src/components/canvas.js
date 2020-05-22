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
        }
        this.tree = props.tree;
        this.state.height = this.tree.getHeight();
        this.update = this.update.bind(this);
        this.dragged = this.dragged.bind(this);
        this.pressed = this.pressed.bind(this);
        this.released = this.released.bind(this);
    }

    // P5
    Sketch = (p) => {
        p.setup = () => {
            p.createCanvas(this.state.width, this.state.height - 40);
        }
   
        p.draw = () => {
            p.background('#34495e');
            this.tree.draw(p, this.state.width);
        }

        p.windowResized = (width, height) => {
            this.tree.resize(width);
            p.resizeCanvas(width, height, false);
            p.redraw();
        }
    }

    update(){
        console.log('update called with tree', this.tree);
        this.state.myP5.windowResized(this.state.width, this.tree.getHeight());
        this.setState((prevState) => {
            return {
                width : prevState.myRef.current.offsetWidth
            }
        });
    }

    componentDidMount() {
        var newWidth = this.state.myRef.current.offsetWidth;
        this.state.myP5 = new p5(this.Sketch, this.state.myRef.current);
        console.log('conponent did mound', newWidth);
        this.setState({
            height : this.tree.getHeight() + 40,
            width : newWidth
        });

        this.state.myP5.windowResized(newWidth, this.tree.getHeight());
        window.addEventListener("resize", this.update);
    }

    pressed(e){
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
            console.log('touch event');
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
                this.tree.moveTree(e.changedTouches[0].clientX - this.initialX, e.changedTouches[0].clientY - this.initialY);
                this.initialX = e.touches[0].clientX;
                this.initialY = e.touches[0].clientY;
                console.log('touch event');
            } else {
                this.tree.moveTree(e.clientX - this.initialX, e.clientY - this.initialY);
                this.initialX = e.clientX;
                this.initialY = e.clientY;
            }
        }
        // console.log('mouse not pressed but moving', e.clientX, e.clientY);
    }
    
    render(){
        return  (
        <Container>
            <Container className='canvas' style={{'height' : this.state.height }}>
                <Row xs={12} md={12} lg={12} noGutters={true} className='justify-content-xs-left'>
                    <Col xs={1} md={1} lg={1}>
                        <a  href="#" className='badge badge-warning' style={{'border-radius' : '100%', 'background-color':'white'}}>X</a>
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
                    <Col xs={5} md={5} lg={5}></Col>
                </Row>
                <Row xs={1} md={1} lg={1} noGutters={true}>
                    <Col>
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