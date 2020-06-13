import React from 'react'
import Header from './header'
import TreeChoices from './treeChoices';
import CanvasContainer from './canvasContainer'
import TreeOperations from './treeOperations'
import Jumbotron from 'react-bootstrap/Jumbotron'

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
                    {/* <h3>Choose a tree type</h3> */}
                    <TreeChoices preferences={this.preferences}/>
                    <TreeOperations triggerUpdate={this.update} treesStrs={this.treesStrs} 
                                    trees={this.trees} preferences={this.preferences} 
                                    ref={this.TreeOperationsRef}/>
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