import React from 'react'
import '../Styles/canvas.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvas from './canvas'
import Button from 'react-bootstrap/Button'
import backArrowSvg from '../resources/back.svg'
import nextArrowSvg from '../resources/next.svg'

class CanvasContainer extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            treesStrs: props.treesStrs,
            children : this.createReferences(props.trees.length),
            upperBound : 2,
            lowerBound : 0,
        }
        this.isCalled = false;
        this.printed = false;
        this.update = this.update.bind(this);
        this.increaseBounds = this.increaseBounds.bind(this);
        this.decreaseBounds = this.decreaseBounds.bind(this);
        this.popTree = this.popTree.bind(this);
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

    increaseBounds(e){
        this.setState((prevState)=>{
            if (prevState.upperBound < prevState.trees.length){
                return ({
                    upperBound : prevState.upperBound + 1,
                    lowerBound : prevState.lowerBound + 1
                });
            }
        });

        e.preventDefault(); // to pevent the default behavior (refreshing the page)
    }

    decreaseBounds(e){
        this.setState((prevState)=>{
            if (prevState.lowerBound > 0){
                return ({
                    upperBound : prevState.upperBound - 1,
                    lowerBound : prevState.lowerBound - 1
                });
            }
        });

        e.preventDefault(); // to pevent the default behavior (refreshing the page)
    }

    popTree(){
        // console.log('pop tree called');
            this.setState(prevState=>{
                if (!this.isCalled){
                    prevState.treesStrs.pop()
                    prevState.trees.shift();
                    this.isCalled = true;
                } else {
                    this.isCalled = false;
                    return ({trees: prevState.trees});
                }
            });

    }
    
    render(){
        return  (
        <Container>
            <Container className="canvasContainer h-auto d-inline-block">
                <br/>
                <Row>
                    <Col>
                        <a href='#'  onClick={this.decreaseBounds}>
                            <img src={backArrowSvg} alt='right arrow'/>
                        </a>
                    </Col>
                    <Col>
                        <a href='#'  onClick={this.increaseBounds}>
                            <img src={nextArrowSvg} alt='right arrow'/>
                        </a>
                    </Col>
                </Row>
                <br/>
                <Row xs={1} s={1} md={1} lg={2} noGutters={true}>
                    {
                        // this.generateCanvases()
                        this.state.trees.map((tree, i) => {
                            this.printed = true;
                            // console.log('creating canvas for tree', i, tree);
                            if ( this.state.lowerBound <= i && i < this.state.upperBound)
                                return (
                                    <Col>
                                        <Canvas topTree={i==0?true:false} popTree={this.popTree} 
                                                key={tree.getId()} ref={this.state.children[i]} 
                                                tree={tree} canvasNo={tree.getId()} treeType={tree.getTreeType()}
                                                updateTreeOperations={this.props.updateTreeOperations}/>
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