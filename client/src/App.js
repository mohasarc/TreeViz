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

class App extends React.Component {
  constructor(props){
    super(props);
  }

  render(){
    return (
      <Router>
        <div className="App">
          <Switch>
            <Route path={'/fullTreeView'} component={DetachedCanvas}/>
            <Route path={'/about'} component={About}/>
            <Route path={'/how-to'} component={HowTo}/>
            <Route path={'/'} exact component={Home}/>
          </Switch>
        </div>
      </Router>
    );
  }
}

export default App;
