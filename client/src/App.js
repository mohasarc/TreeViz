import React from 'react';
import logo from './logo.svg';
import './App.css';
import Header from './components/header';
import TreeChoices from './components/treeChoices';
import CanvasContainer from './components/canvasContainer'
import TreeOperations from './components/TreeOperations'
import { unstable_batchedUpdates } from 'react-dom';

class App extends React.Component {
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
      <div className="App">
        <Header welcomeMsg="TREEVIZ" h="h1"/>
        <Header welcomeMsg="Choose a tree type" h="h2"/>
        <TreeChoices/>
        <TreeOperations triggerUpdate={this.update} trees={this.trees} />
        <CanvasContainer ref={this.canvasContainerRef} trees={this.trees} ></CanvasContainer>
        <br/>
        <footer className="blockquote-footer">
        This website was developped by <a href='https://github.com/mohasarc'>Mohammed S. Yaseen</a>
        </footer>
      </div>
    );
  }
}

export default App;
