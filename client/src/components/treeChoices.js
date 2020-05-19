import React from 'react'
import Button from 'react-bootstrap/Button'
import ButtonGroup from 'react-bootstrap/ButtonGroup'
import DropdownButton from 'react-bootstrap/DropdownButton'
import Dropdown from 'react-bootstrap/Dropdown'
import ToggleButtonGroup from 'react-bootstrap/ToggleButtonGroup'
import ToggleButton from 'react-bootstrap/ToggleButton'
import NavDropdown from 'react-bootstrap/NavDropdown'
import Navbar from 'react-bootstrap/Navbar'
import Nav from 'react-bootstrap/Nav'

class ChoiceButton extends React.Component {
    constructor(props){
        super(props);
        this.name = props.name;
        this.id = props.id;
        this.value = props.value;
    }

    render(){
        return (
        <ToggleButton onClick={this.props.onClick} variant="secondary" value={this.value}>{this.name}</ToggleButton>
        );
    }
}

class TreeChoices extends React.Component{
    constructor(props){
        super(props);
        this.assessed = false;
        this.updateChoice = this.updateChoice.bind(this);
    }

    updateChoice(e){
        if (!this.assessed){
            this.treeChoice = e.target.attributes.treeId.value;
            this.assessed = true;
        }
        else
            this.assessed = false;

        this.props.triggerUpdate();
    }

    render(){
        return (
            <div>
                <ToggleButtonGroup type="radio" className='d-none d-sm-block' name="options" defaultValue={2}>
                    <ToggleButton treeId="binary" onClick={this.updateChoice} variant="secondary" value={1}>Binary Tree</ToggleButton>
                    <ToggleButton treeId="23" onClick={this.updateChoice} variant="secondary" value={2}>2-3 Tree</ToggleButton>
                    <ToggleButton disabled="true" treeId="234" /*onClick={this.updateChoice}*/ variant="secondary" value={3}>2-3-4 Tree</ToggleButton>
                    <ToggleButton disabled="true" treeId="avl" /*onClick={this.updateChoice}*/ variant="secondary" value={4}>AVL Tree</ToggleButton>
                    <ToggleButton disabled="true" treeId="redblack" /*onClick={this.updateChoice}*/ variant="secondary" value={5}>Black-Red Tree</ToggleButton>
                </ToggleButtonGroup>

                <ToggleButtonGroup type="radio" className='d-block d-sm-none' name="options">
                    <ToggleButton variant="secondary" value={1}>Binary Tree</ToggleButton>
                    <ToggleButton variant="secondary" value={2}>2-3 Tree</ToggleButton>
                    <DropdownButton as={ToggleButtonGroup} type="radio" name="options" id="bg-nested-dropdown" variant="secondary">
                        <Dropdown.Item eventKey="3">2-3-4 Tree</Dropdown.Item>
                        <Dropdown.Item eventKey="4">AVL Tree</Dropdown.Item>
                        <Dropdown.Item eventKey="5">Black-Red Tree</Dropdown.Item>
                    </DropdownButton>
                </ToggleButtonGroup>

                {/* <ButtonGroup aria-label="Tree type choices" className='d-none d-sm-block'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                    <ChoiceButton text="2-3-4 Tree"/>
                    <ChoiceButton text="AVL Tree"/>
                    <ChoiceButton text="Black-Red Tree"/>
                </ButtonGroup>
                <ButtonGroup className='d-block d-sm-none'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                </ButtonGroup> */}
                <br/>
            </div>
        );
    }
}

export default TreeChoices;