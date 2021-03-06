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
import GenericTree from '../models/GenericTree'

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
        p.tree = null;

        p.setup = () => {
            var cnv = p.createCanvas(0, 0);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree){
                p.translate(p.tree.tx, p.tree.ty);
                p.scale(p.tree.scale);
                p.tree.draw(p);
            }
        }

        p.createImage = () => {
            var tree = new GenericTree();
            tree.construct(p.tree.treeString);
            tree.setTreeType(p.tree.treeType);
            tree.setId(p.tree.id);
            tree.setScale(p.tree.scale);
            tree.setCenterX(p.tree.getCenterX());
            tree.setCenterY(p.tree.getCenterY());
            // tree.resize(tree.getWidth() + 0.2 * tree.getWidth(), true);
            tree.center();
            // tree.putInView((tree.getWidth() + 0.2 * tree.getWidth())/2);

            var scaleUp = 7000 / tree.getWidth();
            tree.setScale(tree.getScale() * scaleUp);
            var image = p.createGraphics(tree.getWidth() + 0.2 * tree.getWidth(), tree.getHeight());
            image.background('#34495e');
            image.scale(tree.getScale());
            tree.draw(image);

            // Adding copywrites to the image
            image.scale(1/tree.getScale() * 2);
            image.fill('#FFFFF');
            image.textAlign(p.LEFT, p.TOP);
            image.textSize(20);
            image.text('created by TreeViz.tech', 50, 50);
            
            // Saving the image
            image.save( tree.getTreeType() + '.png');
        }

        p.scaleValue = 1;

        p.windowResized = (width, height) => {
            p.resizeCanvas(width, height);
            p.redraw();
        }

        p.redrawCanvas = () => {
            p.redraw();
        }

        p.moveCamera = (deltaX, deltaY) => {
            // Update the current camera location
            p.tree.tx += deltaX;
            p.tree.ty += deltaY;
        }

        p.zoom = (scale, mouseX, mouseY) => {
            p.tree.scale = p.tree.scale * scale;
            p.tree.tx = mouseX * (1-scale) + p.tree.tx * scale;
            p.tree.ty = mouseY * (1-scale) + p.tree.ty * scale;
        }

        p.setTree = (tree) => {
            p.tree = tree;
            if (p.tree){
                p.tree.scale = 1;
                p.tree.tx = 0;
                p.tree.ty = 0;
            }
        }
    }

    update(e){
        this.setState(
            {
            fullScreenTreeIndex : 0,
            leftTreeIndex : 0,
            rightTreeIndex : 1,
            trees : this.props.trees
            }
        );
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

    popTree(id){
        this.setState(prevState=>{
            if (!this.isCalled){
                prevState.treesStrs.pop()
                // prevState.trees.shift();
                prevState.trees.map((tree, index) => {
                    if (tree.getId() == id){
                        prevState.trees.splice(index, 1);
                    }
                });
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
                <Row xs={12} md={12} lg={12}>
                    <Col xs={6} md={4} lg={4}>
                        <a  href='#' className='badge badge-warning' 
                            style={{'border-radius' : '100%'}} 
                            onClick={this.viewNewerTrees}>
                                <div className='icon icon-back' ></div>
                        </a>
                    </Col>
                    <Col className='d-none d-sm-block' xs={4} md={4} lg={4}> {/* Block from view on smalland medium devices*/}
                        <Switch color='default' value='canvacesperpage' 
                                inputProps={{ 'aria-label': 'Switch A' }} 
                                onChange={e=>{this.toggleTreesInView(e.target.checked)}} 
                        />
                    </Col>
                    <Col xs={6} md={4} lg={4}>
                        <a  href='#' className='badge badge-warning' 
                            style={{'border-radius' : '100%'}} 
                            onClick={this.viewOlderTrees}>
                                <div className='icon icon-next' ></div>
                        </a>
                    </Col>
                </Row>
                <br/>
                <Row xs={1} s={1} md={1} lg={this.state.NumTreesInView} noGutters={true}>
                    {   // ****** The tree to the left ******
                        // The conditons to view it
                        this.state.trees.length > this.state.leftTreeIndex && this.state.NumTreesInView > 1
                        // what to view
                        ? <Col> <Canvas topTree={true} popTree={this.popTree}
                                key={this.state.trees[this.state.leftTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.leftTreeIndex]} canvasNo={this.state.trees[this.state.leftTreeIndex].getId()} treeType={this.state.trees[this.state.leftTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                p5={this.myP5_1} theNode={this.node1} detached={false}/> 
                                <br/>
                         </Col>
                        : <Col/>
                    }
                    {   // ****** The tree to the right ******
                        // The conditions to view it
                        this.state.trees.length > this.state.rightTreeIndex && this.state.NumTreesInView > 1
                        // what to view
                        ? <Col> <Canvas topTree={true} popTree={this.popTree}
                                key={this.state.trees[this.state.rightTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.rightTreeIndex]} canvasNo={this.state.trees[this.state.rightTreeIndex].getId()} treeType={this.state.trees[this.state.rightTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                theNode={this.node2} p5={this.myP5_2} detached={false}/>
                                <br/>
                         </Col>
                        : <Col/>
                    }
                    {   // ****** The Full Screen tree ******
                        // The conditions to view it
                        this.state.trees.length > this.state.fullScreenTreeIndex && this.state.NumTreesInView < 2
                        // what to view
                        ? <Col> <Canvas topTree={true} popTree={this.popTree}
                                key={this.state.trees[this.state.fullScreenTreeIndex].getId()} ref={this.state.child1}
                                tree={this.state.trees[this.state.fullScreenTreeIndex]} 
                                canvasNo={this.state.trees[this.state.fullScreenTreeIndex].getId()} 
                                treeType={this.state.trees[this.state.fullScreenTreeIndex].getTreeType()}
                                updateTreeOperations={this.props.updateTreeOperations}
                                theNode={this.node3} p5={this.myP5_3} detached={false}/>
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