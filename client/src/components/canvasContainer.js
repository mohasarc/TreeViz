import React from 'react'
import '../Styles/canvas.css'
import '../Styles/buttons.css'
import Container from 'react-bootstrap/Container'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import Canvas from './canvas'
import Button from 'react-bootstrap/Button'
import backArrowSvg from '../resources/back.svg'
import nextArrowSvg from '../resources/next.svg'
import Form from 'react-bootstrap/Form'
import ReactDOM from 'react-dom'
import Switch from '@material-ui/core/Switch';
import p5 from 'p5'

class CanvasContainer extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            treesStrs: props.treesStrs,
            leftTreeIndex : 0,
            rightTreeIndex : 1,
            NumTreesInView : 2,
            fullScreenTreeIndex : 0,
        }
        this.isCalled = false;
        this.printed = false;
        this.update = this.update.bind(this);
        this.viewOlderTrees = this.viewOlderTrees.bind(this);
        this.viewNewerTrees = this.viewNewerTrees.bind(this);
        this.popTree = this.popTree.bind(this);
        this.toggleTreesInView = this.toggleTreesInView.bind(this);

        // Creating the p5 object for the two canvaces
        this.node1 = document.createElement('div');
        this.node2 = document.createElement('div');
        this.node3 = document.createElement('div');
        this.myP5_1 = new p5(this.Sketch, this.node1);
        this.myP5_2 = new p5(this.Sketch, this.node2);
        this.myP5_3 = new p5(this.Sketch, this.node3);
    }

    Sketch = (p) => {
        p.width = 0;
        p.height = 0;
        p.tree = null;

        p.setup = () => {
            var cnv = p.createCanvas(p.width, p.height - 40);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree)
                p.tree.draw(p, p.width);
        }

        p.windowResized = (width, height) => {
            if (p.tree)
                p.tree.resize(width);
            p.resizeCanvas(width, height);
            p.redraw();
        }
    }

    update(e){
        this.setState({
            fullScreenTreeIndex : 0,
            leftTreeIndex : 0,
            rightTreeIndex : 1,
            trees : this.props.trees});
    }

    viewOlderTrees(e){
        this.setState((prevState)=>{
            // Local variables
            var newFullScreenTreeIndex = prevState.fullScreenTreeIndex;
            var newLeftTreeIndex = prevState.leftTreeIndex;
            var newRightTreeIndex = prevState.rightTreeIndex;

            // if not the last tree
            if (prevState.fullScreenTreeIndex < prevState.trees.length - 1){
                newFullScreenTreeIndex = prevState.fullScreenTreeIndex + 1;
            }
            // if tree to the right isn't the last tree
            if (prevState.rightTreeIndex < prevState.trees.length - 1 ) {
                newLeftTreeIndex = prevState.leftTreeIndex + 1;
                newRightTreeIndex = prevState.rightTreeIndex + 1;
            }

            // Set the updated values
            return ({
                fullScreenTreeIndex : newFullScreenTreeIndex,
                leftTreeIndex : newLeftTreeIndex,
                rightTreeIndex : newRightTreeIndex,
            });
        });

        e.preventDefault(); // to pevent the default behavior (refreshing the page)
    }

    viewNewerTrees(e){
        this.setState((prevState)=>{
            // Local variables
            var newFullScreenTreeIndex = prevState.fullScreenTreeIndex;
            var newLeftTreeIndex = prevState.leftTreeIndex;
            var newRightTreeIndex = prevState.rightTreeIndex;

            // if is not the first tree in array
            if (prevState.fullScreenTreeIndex > 0 ){
                newFullScreenTreeIndex = prevState.fullScreenTreeIndex - 1;
            }
            // if left tree is not the first tree in array
            if (prevState.leftTreeIndex > 0){
                newLeftTreeIndex = prevState.leftTreeIndex - 1;
                newRightTreeIndex = prevState.rightTreeIndex - 1;
            }

            return ({
                fullScreenTreeIndex : newFullScreenTreeIndex,
                leftTreeIndex : newLeftTreeIndex,
                rightTreeIndex : newRightTreeIndex,
            });
        });

        e.preventDefault(); // to pevent the default behavior (refreshing the page)
    }

    popTree(){
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

    toggleTreesInView(checked){
        // view one tree
        if (checked == true){
            this.setState({NumTreesInView : 1});
        } 
        // view two trees
        else {
            this.setState(prevState=>{
                return ({NumTreesInView : 2}
                );
            }
            );
        }
    }
    
    render(){
        return  (
        <Container>
            <Container className="canvasContainer h-auto d-inline-block">
                <br/>
                <Row>
                    <Col>
                        <a href='#'   onClick={this.viewNewerTrees}>
                            <span className='icon icon-back' ></span>
                        </a>
                    </Col>
                    <Col className='d-none d-sm-block'> {/* Block from view on smalland medium devices*/}
                        <Switch color='default' value='canvacesperpage' 
                                inputProps={{ 'aria-label': 'Switch A' }} 
                                onChange={e=>{this.toggleTreesInView(e.target.checked)}} 
                        />
                    </Col>
                    <Col>
                        <a href='#'  onClick={this.viewOlderTrees}>
                            <span className='icon icon-next' ></span>
                        </a>
                    </Col>
                </Row>
                <br/>
                <Row xs={1} s={1} md={1} lg={this.state.NumTreesInView} noGutters={true}>
                    {   // ****** The tree to the left ******
                        // The conditons to view it
                        this.state.trees.length > this.state.leftTreeIndex && this.state.NumTreesInView > 1
                        // what to view
                        ? <Col> <Canvas topTree={this.state.leftTreeIndex == 0 ? true : false} popTree={this.popTree}
                                key={this.state.trees[this.state.leftTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.leftTreeIndex]} canvasNo={this.state.trees[this.state.leftTreeIndex].getId()} treeType={this.state.trees[this.state.leftTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                p5={this.myP5_1} theNode={this.node1}/> 
                                <br/>
                         </Col>
                        : <Col/>
                    }
                    {   // ****** The tree to the right ******
                        // The conditions to view it
                        this.state.trees.length > this.state.rightTreeIndex && this.state.NumTreesInView > 1
                        // what to view
                        ? <Col> <Canvas topTree={this.state.rightTreeIndex == 0 ? true : false} popTree={this.popTree}
                                key={this.state.trees[this.state.rightTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.rightTreeIndex]} canvasNo={this.state.trees[this.state.rightTreeIndex].getId()} treeType={this.state.trees[this.state.rightTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                theNode={this.node2}
                                p5={this.myP5_2}/>
                                <br/>
                         </Col>
                        : <Col/>
                    }
                    {   // ****** The Full Screen tree ******
                        // The conditions to view it
                        this.state.trees.length > this.state.fullScreenTreeIndex && this.state.NumTreesInView < 2
                        // what to view
                        ? <Col> <Canvas topTree={this.state.fullScreenTreeIndex == 0 ? true : false} popTree={this.popTree}
                                key={this.state.trees[this.state.fullScreenTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.fullScreenTreeIndex]} 
                                canvasNo={this.state.trees[this.state.fullScreenTreeIndex].getId()} 
                                treeType={this.state.trees[this.state.fullScreenTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                theNode={this.node3}
                                p5={this.myP5_3}/>
                                <br/>
                         </Col>
                        : <Col/>
                    }
                </Row>
            </Container>
        </Container>
        );
    }
}

export default CanvasContainer;