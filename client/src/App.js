import React from 'react';
// import logo from './logo.svg';
import './App.css';
import Home from './components/home';
import About from './components/About';
import HowTo from './components/HowTo';
import DetachedCanvas from './components/detachedCanvas'
import { unstable_batchedUpdates } from 'react-dom';
// import {Router, Route} from 'react-router';
// import { createBrowserHistory } from 'history';
import {BrowserRouter as Router, Switch, Route} from 'react-router-dom';
import history from "./utils/history";

class App extends React.Component {
  constructor(props){
    super(props);
  }

  render(){
    return (
      <Router history={history}>
        <div className="App">
          <Switch>
            <Route path={'/fullTreeView'} component={DetachedCanvas}/>
            <Route path={'/about'} component={About}/>
            <Route path={'/how-to'} component={HowTo}/>
            <Route path={'/'} exact component={()=><Home initialTreeChoice={'23T'} 
                                                         order={3} 
                                                         title={'TreeViz - a tree data structures visualization tool'} 
                                                         description={'The best tree data structure visualization tool, TreeViz is used to visualize and convert multiple different types of trees including Binary, AVL, and B-tree. TreeViz includes supports many features including Auto generate, Zoom in / out, Full screen, Animation, Store tree.'}/>}
            />
            <Route path={'/2-3-tree'} exact component={()=><Home initialTreeChoice={'23T'} 
                                                                order={3}  
                                                                title={'2-3 Tree Visualization using TreeViz'} 
                                                                description={'B-Trees. Degree = 3. Propagate smaller value. prioritize inorder predecessor / successor. prioritize rotate right / left. Split / Merge.  Animation Speed. Full screen. Store tree. Zoom in / out. Auto generate. Algorithm Visualizations. convert to binary search tree. convert to AVL tree. convert to B-tree'}/>}
            />
            <Route path={'/2-3-4-tree'} exact component={()=><Home initialTreeChoice={'234'} 
                                                                  order={4}  
                                                                  title={'2-3-4 Tree Visualization using TreeViz'} 
                                                                  description={'B-Trees. Degree = 4. Propagate smaller value. prioritize inorder predecessor / successor. prioritize rotate right / left. Split / Merge.  Animation Speed. Full screen. Store tree. Zoom in / out. Auto generate. Algorithm Visualizations. convert to binary search tree. convert to AVL tree. convert to B-tree'}/>}
            />
            <Route path={'/binary-tree'} exact component={()=><Home initialTreeChoice={'BST'} 
                                                                   order={0}  
                                                                   title={'BST - Binary Search Tree Visualization using TreeViz'} 
                                                                   description={'Binary Search Tree ( BST-Trees ). While removing, replace with predecessor. Animation Speed. Full screen. Store tree. Zoom in / out. Auto generate. Algorithm Visualizations. convert to AVL tree. convert to B-tree'}/>}
            />
            <Route path={'/avl-tree'} exact component={()=><Home initialTreeChoice={'AVL'} 
                                                                order={0}  
                                                                title={'AVL Tree Visualization using TreeViz'} 
                                                                description={'AVL-Trees. Preferences. prioritize inorder predecessor / successor. prioritize rotate right / left. Split / Merge.  Animation Speed. Full screen. Store tree. Zoom in / out. Auto generate. Algorithm Visualizations. convert to binary tree. convert to AVL tree. convert to B-tree'}/>}
            />
            <Route path={'/b-tree'} exact component={()=><Home initialTreeChoice={'B-T'} 
                                                              order={5} 
                                                              title={'B-Tree Visualization using TreeViz'} 
                                                              description={'B-Trees. Degree = 5 , 6 , 7 , 8 ... inf. . Propagate smaller value. prioritize inorder predecessor / successor. prioritize rotate right / left. Split / Merge.  Animation Speed. Full screen. Auto generate. Store tree. Zoom in / out. Algorithm Visualizations. convert to binary tree. convert to AVL tree. convert to B-tree'}/>}
            />
          </Switch>
        </div>
      </Router>
    );
  }
}

export default App;
