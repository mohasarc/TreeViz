import React from 'react'
import Header from './header'
import TreeChoices from './treeChoices';
import CanvasContainer from './canvasContainer'
import TreeOperations from './treeOperations'
import Jumbotron from 'react-bootstrap/Jumbotron'
import Col from 'react-bootstrap/Col'
import Row from 'react-bootstrap/Row'
import Container from 'react-bootstrap/Container'

class Home extends React.Component{
    constructor(props){
        super(props);
        this.TreeOperationsRef = React.createRef();
        this.canvasContainerRef = React.createRef();
        this.trees = [];
        this.treesStrs = [];
        this.treeChoice = [];
        this.treeChoice[0] = '23';
        this.preferences = {
            'type' : {'name' : '2-3 tree'      , 'value' : '23T'},
            'order' : 3,
            'propagateSmallerValue' : false,
            'prioritizeInorderPredecessor' : false,
            'prioritizeRotateLeft' : false,
            'replaceWithPredecessor' : false
        };
        this.update = this.update.bind(this);
        this.updateTreeOperations = this.updateTreeOperations.bind(this);
    }

    update(){
        this.canvasContainerRef.current.update();
        // console.log('all data stored so far **********');
        // console.log(this.trees, this.treesStrs);
    }

    updateTreeOperations(treeDescription){
        this.TreeOperationsRef.current.setTreeDescription(treeDescription);
    }
  
    render(){
        return (
            <div>
                <Header/>
                <Jumbotron>
                    <Container>
                        <Row xs={12} md={12} lg={12}>
                            <Col xs={12} md={3} lg={3}>
                                <TreeChoices preferences={this.preferences}/>
                            </Col>
                            <Col xs={12} md={9} lg={9}>
                                <TreeOperations triggerUpdate={this.update} treesStrs={this.treesStrs} 
                                            trees={this.trees} preferences={this.preferences} 
                                            ref={this.TreeOperationsRef}/>
                            </Col>
                        </Row>
                    </Container>
                    {/* <h3>Choose a tree type</h3> */}


                    <CanvasContainer updateTreeOperations={this.updateTreeOperations} 
                                     ref={this.canvasContainerRef} treesStrs={this.treesStrs} 
                                     trees={this.trees} ></CanvasContainer>
                    <br/>
                </Jumbotron>
                <footer className="blockquote-footer">
                This website was developped by <a href='https://github.com/mohasarc'>Mohammed S. Yaseen</a>
                </footer>
                <br/>
            </div>
        );
    }
}

export default Home;