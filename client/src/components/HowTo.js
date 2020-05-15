import React from 'react'
import Header from './header'
import Jumbotron from 'react-bootstrap/Jumbotron'
class HowTo extends React.Component{
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
                    <h3>
                        How to use TreeViz
                    </h3>
                    <br/>
                    <p style={{'text-align': 'left'}}>    There are two different ways create a tree. Either start with and empty tree <br/>
                        and add values using + button, or use tree string structure to describe a <br/>
                        particular tree then perform operations on it. <br/>
                    <br/>
                    <p> What is tree string? <br/>
                     It is a string that explains the tree.<br/>
                     - Each number between {'{}'} belonges to the same node<br/>
                     - Each node's children are placed between ()<br/>
                        ex:<br/>
                        {'     {5,7}'}    <br/>
                        {' /     |     \\'}  <br/>
                        {'{3}   {6}   {8}'}<br/>
                       tree string : {'{5,7}({3}{6}{8})'}<br/>
                    </p>
                    <p>
                        Currently only 2-3 tree is implemented and it can only construct a tree from a tree string
                        and add values to empty or non-empty tree.
                    </p>
                    <p>
                        Important note: the tree string should contain a valid 2-3 tree that is if a node has one item,
                        it can have only two children and if it has two items it must have 3 children.
                    </p>
                    </p>
                </Jumbotron>
                <footer className="blockquote-footer">
                This website was developped by <a href='https://github.com/mohasarc'>Mohammed S. Yaseen</a>
                </footer>
                <br/>
            </div>
        );
    }
}

export default HowTo;