import React from 'react';
import Header from './header';
import Jumbotron from 'react-bootstrap/Jumbotron';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import {Helmet} from 'react-helmet'

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
                <Helmet>
                    <title>About TreeViz</title>
                    <meta name="description" content="More information about TreeViz tool." />
                </Helmet>
                <Header/>
                <Jumbotron>
                    <Row xs={12} md={12} lg={12}>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>This website was Developped by Mohammed S. Yaseen. It is intended to be a helpful tool
                        to visualize trees mainly for study purposes. Currently, the app is under development
                        and many features are yet to be implemented.
                        </Col>
                    </Row>
                    <br/>
                    <Row>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                        latest update: 23/10/2020
                        </Col>
                    </Row>
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