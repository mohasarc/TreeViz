import React from 'react'
import Navbar from 'react-bootstrap/Navbar'
import Nav from 'react-bootstrap/Nav'
import Form from 'react-bootstrap/Form'
import FormControl from 'react-bootstrap/FormControl'
import Button from 'react-bootstrap/Button'

class Header extends React.Component{
    constructor(props){
        super(props);
        this.welcomeMsg = props.welcomeMsg;
        this.h = props.h;
    }

    render(){
        return (
            <Navbar bg="dark" variant="dark">
                <Navbar.Brand href="/">TreeViz</Navbar.Brand>
                <Nav className="mr-auto">
                <Nav.Link href="/">Home</Nav.Link>
                <Nav.Link href="/about">About</Nav.Link>
                <Nav.Link href="/how-to">How to use</Nav.Link>
                </Nav>
            </Navbar>
        );
    }
}

export default Header;