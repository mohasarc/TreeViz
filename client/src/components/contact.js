import React from 'react';
import Header from './header';
import Jumbotron from 'react-bootstrap/Jumbotron';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import {Helmet} from 'react-helmet'

class Contact extends React.Component{
    constructor(props){
        super();
    }

    render(){
        return (
            <div>
                <Helmet>
                    <title>About TreeViz</title>
                    <meta name="description" content="Contact TreeViz to suggest changes and get more information." />
                </Helmet>
                <Header/>
                <Jumbotron>
                    <Row xs={12} md={12} lg={12}>
                        <Col md={{ span: 6, offset: 3 }} lg={{ span: 6, offset: 3 }} style={{"text-align":"left"}}>We are open to suggestions and feature requests. we are availeble through this email: <a href='mailto: moha.98.1900@gmail.com'>moha.98.1900@gmail.com</a>
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

export default Contact;