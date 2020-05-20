import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import Badge from 'react-bootstrap/Badge'
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
        this.initialX = e.clientX;
        this.initialY = e.clientY;
    }

    released(e){
        this.mousePressed = false;
    }

    dragged(e){
        if (this.mousePressed){
            this.tree.moveTree(e.clientX - this.initialX, e.clientY - this.initialY);
            // update initial values
            this.initialX = e.clientX;
            this.initialY = e.clientY;
        }
        // console.log('mouse not pressed but moving', e.clientX, e.clientY);
    }
    
    render(){
        return  (
        <Container>
            <Container className="canvas" style={{'height' : this.state.height }}>
                <Row xs={3} md={3} lg={3} noGutters={true}>
                    <Col>
                        <Badge variant="warning">
                            {this.state.treeType}
                        </Badge>
                    </Col>
                    <Col>
                        <Canvasno no={this.state.canvasNo}></Canvasno>
                    </Col>
                </Row>
                <Row xs={1} md={1} lg={1} noGutters={true}>
                    <Col>
                        <div onMouseDown={this.pressed} onMouseMove={this.dragged} onMouseUp={this.released} ref={this.state.myRef} />
                    </Col>
                </Row>
            </Container>
        </Container>
        );
    }
}

export default Canvas;