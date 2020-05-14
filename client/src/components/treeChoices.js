import React from 'react'
import Button from 'react-bootstrap/Button'
import ButtonGroup from 'react-bootstrap/ButtonGroup'
import DropdownButton from 'react-bootstrap/DropdownButton'
import Dropdown from 'react-bootstrap/Dropdown'

function ChoiceButton(props){
    return <Button variant="secondary" >{props.text}</Button>;
}

class TreeChoices extends React.Component{
    constructor(props){
        super(props);
    }

    render(){
        return (
            <div>
                <ButtonGroup aria-label="Tree type choices" className='d-none d-sm-block'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                    <ChoiceButton text="2-3-4 Tree"/>
                    <ChoiceButton text="AVL Tree"/>
                    <ChoiceButton text="Black-Red Tree"/>
                </ButtonGroup>
                <ButtonGroup className='d-block d-sm-none'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                    <DropdownButton as={ButtonGroup} id="bg-nested-dropdown" variant="secondary">
                        <Dropdown.Item eventKey="3">2-3-4 Tree</Dropdown.Item>
                        <Dropdown.Item eventKey="4">AVL Tree</Dropdown.Item>
                        <Dropdown.Item eventKey="5">Black-Red Tree</Dropdown.Item>
                    </DropdownButton>
                </ButtonGroup>
                <br/>
            </div>
        );
    }
}

export default TreeChoices;