import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvas from './canvas'

class CanvasContainer extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            children : this.createReferences(props.trees.length)
        }
        this.printed = false;
        this.update = this.update.bind(this);
    }

    createReferences(num){
        var refs = [];

        for (let i = 0; i < num; i++){
            refs.push(React.createRef());
        }

        return refs;
    }

    update(e){
        this.setState((prevState) => {
            return {trees : this.props.trees,
                    children : this.createReferences(this.props.trees.length)
                   }
        });
        // console.log('I got the uodate', this.state.trees);
        this.state.children.map((child)=> {
            child.current.update();
        });
    }
    
    render(){
        return  (
        <Container>
            <Container className="canvasContainer h-auto d-inline-block">
                <br/>
                <Row xs={1} s={1} md={1} lg={2} noGutters={true}>
                    {
                        this.state.trees.map((tree, i) => {
                            this.printed = true;
                            console.log('creating canvas for tree', i, tree);

                            return (
                                <Col>
                                    <Canvas ref={this.state.children[i]} tree={tree} canvasNo={i + 1}/>
                                    <br/>
                                </Col>
                            );
                        })
                    }
                </Row>
            </Container>
        </Container>
        );
    }
}

export default CanvasContainer;