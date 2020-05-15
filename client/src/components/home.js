import React from 'react'
import Header from './header'
import TreeChoices from './treeChoices';
import CanvasContainer from './canvasContainer'
import TreeOperations from './treeOperations'
import Jumbotron from 'react-bootstrap/Jumbotron'

class Home extends React.Component{
    constructor(props){
        super(props);
        this.canvasContainerRef = React.createRef();
        this.trees = [];
    
        this.update = this.update.bind(this);
    }

    update(){
        this.canvasContainerRef.current.update();
    }
  
      
    render(){
        return (
            <div>
                <Header/>
                <Jumbotron>
                    <br/>
                    <h3>Choose a tree type</h3>
                    <TreeChoices/>
                    <TreeOperations triggerUpdate={this.update} trees={this.trees} />
                    <CanvasContainer ref={this.canvasContainerRef} trees={this.trees} ></CanvasContainer>
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