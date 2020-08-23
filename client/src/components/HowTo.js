import React from 'react';
import Header from './header';
import Jumbotron from 'react-bootstrap/Jumbotron';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';

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
                    <Row xs={12} md={12} lg={12}>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                            <h3> How to use TreeViz </h3>
                        </Col>
                    </Row>
                    <br/>
                    <Row xs={12} md={12} lg={12}>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                            There are two different ways create a tree. Either start with and empty tree
                            and add values using + button, or use tree string structure to describe a
                            particular tree then perform operations on it. A third way also exists that is
                            generating a random tree using random tree generator by pressing Generate button.
                        </Col>
                    </Row>
                    <br/>
                    <Row>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                         <h5>  What is tree string?  </h5>
                        </Col>
                    </Row>
                    <Row>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>
                        It is a string that explains the tree such that:<br/>
                            &nbsp;&nbsp;&nbsp;&nbsp;- numbers separated by commas and between {'{}'} belonges to the same node<br/>
                            &nbsp;&nbsp;&nbsp;&nbsp;- Each node's children are separated by commas and placed between ()<br/>
                            example tree string : {'{5,7}({3}{6}{8,9})'}<br/>
                            corresponding tree :
                        </Col>
                    </Row>
                    <Row>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"center"}}>
                            {'     {5,7}'}    <br/>
                            {' /     |     \\'}  <br/>
                            {'{3}   {6}   {8,9}'}<br/>
                        <br/>

                        </Col>
                    </Row>
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

export default HowTo;