import React from 'react'
import Header from './header'
import Jumbotron from 'react-bootstrap/Jumbotron'

class About extends React.Component{
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
                    <p>This website was Developped by Mohammed S. Yaseen. It is intended to be a helpful tool
                        to visualize trees mainly for study purposes. Currently, the app is under development
                        and many features are yet to be implemented..
                    </p>
                    <p>
                        Node js, Express js, and React js were used to develop this website, 
                        in addition to using node addons api to compile and run c++ logic libraries, s.t. 
                        the trees logic, in the backend.
                    </p>
                    <p>
                        latest update: 15/5/2020
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

export default About;