import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvas from './canvas'
import Button from 'react-bootstrap/Button'

class CanvasContainer extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            children : this.createReferences(props.trees.length),
            upperBound : 2,
            lowerBound : 0,
        }
        this.printed = false;
        this.update = this.update.bind(this);
        this.increaseBounds = this.increaseBounds.bind(this);
        this.decreaseBounds = this.decreaseBounds.bind(this);
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
            if (child.current != null)
                child.current.update();
        });
    }

    increaseBounds(){
        this.setState((prevState)=>{
            if (prevState.upperBound < prevState.trees.length){
                return ({
                    upperBound : prevState.upperBound + 1,
                    lowerBound : prevState.lowerBound + 1
                });
            }
        });
    }

    decreaseBounds(){
        this.setState((prevState)=>{
            if (prevState.lowerBound > 0){
                return ({
                    upperBound : prevState.upperBound - 1,
                    lowerBound : prevState.lowerBound - 1
                });
            }
        });
    }

    // generateCanvases(){
    //     this.setState(()=>{
            
    //     })
    //     // reversin the trees
    //     var treesRev = [];
    //     for (let i = this.state.trees.length - 1; i >= 0;i--){
    //         treesRev.push(this.state.trees[i]);
    //         // console.log(treesRev[i - this.state.trees.length])
    //     }

    //     console.log(treesRev);

    //     return (
    //             treesRev.map((tree, i) => {
    //             this.printed = true;
    //             console.log('creating canvas for tree', i, tree);

    //             return (
    //                 <Col>
    //                     <Canvas ref={this.state.children[i]} tree={tree} canvasNo={i + 1}/>
    //                     <br/>
    //                 </Col>
    //             );
    //         })
    //     );
    // }
    
    render(){
        return  (
        <Container>
            <Container className="canvasContainer h-auto d-inline-block">
                <br/>
                <Row>
                    <Col>
                        <Button onClick={this.decreaseBounds} variant="outline-warning"style={{'border-radius' : '100%', 'background-color':'white'}}>
                            {"<"}
                        </Button>
                    </Col>
                    <Col>
                        <Button onClick={this.increaseBounds} variant="outline-warning"style={{'border-radius' : '100%', 'background-color':'white'}}>
                            >
                        </Button>
                    </Col>
                </Row>
                <br/>
                <Row xs={1} s={1} md={1} lg={2} noGutters={true}>
                    {
                        // this.generateCanvases()
                        this.state.trees.map((tree, i) => {
                            this.printed = true;
                            console.log('creating canvas for tree', i, tree);
                            if ( this.state.lowerBound <= i && i < this.state.upperBound)
                                return (
                                    <Col>
                                        <Canvas key={this.state.trees.length - i} ref={this.state.children[i]} tree={tree} canvasNo={this.state.trees.length - i} treeType={tree.getTreeType()}/>
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