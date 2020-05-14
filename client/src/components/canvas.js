import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvasno from './canvasno'
import p5 from 'p5'

/**
 * The canvas component
 */
class Canvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            height : 900,
            width : 400,
            canvasNo : props.canvasNo,
            myRef : React.createRef(),
        }
        this.tree = props.tree;
        this.state.height = this.tree.getHeight();
        this.update = this.update.bind(this);
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
        this.state.myP5.windowResized(this.state.myRef.current.offsetWidth, this.tree.getHeight());
        this.setState((prevState) => {
            return {
                width : prevState.myRef.current.offsetWidth
            }
        });
    }

    componentDidMount() {
        this.state.myP5 = new p5(this.Sketch, this.state.myRef.current);
        this.setState({
            height : this.tree.getHeight() + 40,
            width : this.state.myRef.current.offsetWidth
        });
        this.state.myP5.windowResized(this.state.myRef.current.offsetWidth, this.tree.getHeight());
        // this.state.myP5.draw.bind(this);
        window.addEventListener("resize", this.update);
    }
    
    render(){
        return  (
        <Container>
            <Container className="canvas" style={{'height' : this.state.height}}>
                <Row xs={12} md={12} lg={12} noGutters={true}>
                    <Col >
                        <Canvasno no={this.state.canvasNo}></Canvasno>
                    </Col>
                </Row>
                <Row xs={1} md={1} lg={1} noGutters={true}>
                    <Col>
                        <div ref={this.state.myRef} />
                    </Col>
                </Row>
            </Container>
        </Container>
        );
    }
}

export default Canvas;