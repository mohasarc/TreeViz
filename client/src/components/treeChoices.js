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

import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'

import DialogSelect from './DialogSelect'

import TextField from '@material-ui/core/TextField';
import Autocomplete from '@material-ui/lab/Autocomplete';
import Grid from '@material-ui/core/Grid';
import Container from 'react-bootstrap/Container';

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
        this.updateChoice = this.updateChoice.bind(this);
        this.preferences = props.preferences;
        this.state = {key : 3};
        this.treeOptions = [
            {'name' : 'Binary tree'   , 'value' : 'BST'},
            {'name' : 'AVL tree'      , 'value' : 'AVL'},
            {'name' : 'Red-Black tree', 'value' : 'RBT'},
            {'name' : '2-3 tree'      , 'value' : '23T'},
            {'name' : '2-3-4 tree'    , 'value' : '234'},
            {'name' : 'B-tree'        , 'value' : 'B-T'},
        ];
    }

    updateChoice(e){
        var choiceIndex = parseInt(e.target.dataset.optionIndex);
        if (this.treeOptions[choiceIndex].value == '234')
            this.preferences.order = 4;
        if (this.treeOptions[choiceIndex].value == '23T')
            this.preferences.order = 3;
        this.preferences.type = this.treeOptions[choiceIndex];
        this.setState({key : this.preferences.order});
    }

    render(){
        return (

            <Container>
                <Row xs={12} md={12} lg={12}>
                    <Col xs={12} md={3} lg={3}>
                        <Autocomplete
                            id="choose-tree-combo-box"
                            options={this.treeOptions}
                            getOptionLabel={(option) => option.name}
                            style={{ width: 300 }}
                            onChange={this.updateChoice}
                            disableClearable={true}
                            renderInput={(params) => <TextField {...params} label="Choose a tree type" variant="outlined" />}
                        />
                        <br/>
                    </Col>
                    <Col xs={12} md={3} lg={3}>
                        <Grid container direction="row" justify="center" alignItems="center" spacing={0}>
                            <DialogSelect key={this.state.key} preferences={this.preferences}/>
                        </Grid>
                    </Col>
                </Row>
            </Container>



            // <Grid container direction="row" justify="flex-start" alignItems="baseline" spacing={0}>
            //     <Grid item xs={4} lg={3} spacing={0}>

            //     </Grid>
            //     <Grid item xs={4} lg={2} spacing={0}>

            //     </Grid>
            // </Grid>


            // <div>
            //     <Row xs={12} md={12} lg={12}>
                    /* <Col xs={6} md={6} lg={6}>
                        <ToggleButtonGroup type="radio" className='d-none d-sm-block' name="options" defaultValue={2}>
                            <ToggleButton treeId="binary" onClick={this.updateChoice} variant="secondary" value={1}>Binary Tree</ToggleButton>
                            <ToggleButton treeId="23" onClick={this.updateChoice} variant="secondary" value={2}>2-3 Tree</ToggleButton>
                            <ToggleButton disabled="true" treeId="234" onClick={this.updateChoice} variant="secondary" value={3}>2-3-4 Tree</ToggleButton>
                            <ToggleButton disabled="true" treeId="avl" onClick={this.updateChoice} variant="secondary" value={4}>AVL Tree</ToggleButton>
                            <ToggleButton disabled="true" treeId="redblack" onClick={this.updateChoice} variant="secondary" value={5}>Black-Red Tree</ToggleButton>
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
                    </Col> */
                //     <Col xs={6} md={6} lg={6}>

                //     </Col>
                //     <Col xs={6} md={6} lg={6}>
                //     </Col>
                // </Row>





                /* <ButtonGroup aria-label="Tree type choices" className='d-none d-sm-block'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                    <ChoiceButton text="2-3-4 Tree"/>
                    <ChoiceButton text="AVL Tree"/>
                    <ChoiceButton text="Black-Red Tree"/>
                </ButtonGroup>
                <ButtonGroup className='d-block d-sm-none'>
                    <ChoiceButton text="Binary Tree"/>
                    <ChoiceButton text="2-3 Tree"/>
                </ButtonGroup> */
            //     <br/>
            // </div>
        );
    }
}

export default TreeChoices;