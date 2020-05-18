import React from 'react'
import Button from 'react-bootstrap/Button'
import Container from 'react-bootstrap/Container'
import GenericTree from '../models/GenericTree'
import FormControl from 'react-bootstrap/FormControl'
import InputGroup from 'react-bootstrap/InputGroup'
import axios from 'axios'
import { unstable_batchedUpdates } from 'react-dom'

class TreeOperations extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            reference : React.createRef(),
            description : React.createRef()
        }
        this.triggerUpdate = props.triggerUpdate;
        this.isCalled = false;
        this.addToArray = this.addToArray.bind(this);
        this.removeFromArray = this.removeFromArray.bind(this);
        this.buildTree = this.buildTree.bind(this);
    }

    addToArray(e){
        this.setState(state => {
            if (!this.isCalled){
                // this.state.tree.insert(this.state.reference.current.value);
                var curTreeString;
                this.state.trees.length >= 1 
                ? curTreeString = this.state.trees[this.state.trees.length - 1].getTreeString()
                : curTreeString = '';

                axios.post('/api/trees/addValue', {value : this.state.reference.current.value,
                                         treeString : curTreeString,
                                         treeChoice : this.props.treeChoice[0]
                                        }
                            ).then((response) => {

                    var treeString = response.data.treeString;
                    if (treeString){
                        var tmpTree = new GenericTree();
                        tmpTree.construct(treeString);
                        tmpTree.buildTreeMatrixCaller();
                        tmpTree.organizeTreeMatrix();
                        this.state.trees.push(tmpTree);
                        this.triggerUpdate();
                    }
                });

                this.isCalled = true;
            } else {
                this.isCalled = false;
            }
        });
        
        this.isCalled = false;
        e.preventDefault();
    }

    removeFromArray(e){
        e.preventDefault();

        this.setState(state => {
            console.log('remove called', this.state.reference.current.value);
            // return {};
        })
    }

    buildTree(e){   
        this.setState((prevState)=>{
            if (!this.isCalled){
                axios.post('/api/trees/sendTree', {treeString : this.state.description.current.value,
                                                   treeChoice : this.props.treeChoice[0]}).then((response) => {
                    var treeString = response.data.treeString;
                    if (treeString){
                        var tmpTree = new GenericTree();
                        tmpTree.construct(treeString);
                        tmpTree.buildTreeMatrixCaller();
                        tmpTree.organizeTreeMatrix();
                        this.state.trees.push(tmpTree);
                        this.triggerUpdate();
                    }
                });

                this.isCalled = true;
            } else {
                this.isCalled = false;
            }
        });

        e.preventDefault();
    }

    render(){
        return (
            <Container>
                <InputGroup className="mb-3">
                    <FormControl
                    ref={this.state.reference}
                    placeholder="Enter a value"
                    aria-label="Enter a value"
                    aria-describedby="basic-addon2"
                    />
                    <InputGroup.Append>
                    <Button variant="outline-secondary" onClick={this.addToArray}>+</Button>
                    <Button variant="outline-secondary" onClick={this.removeFromArray}>-</Button>
                    </InputGroup.Append>
                </InputGroup>
                <InputGroup className="mb-3">
                    <FormControl
                    ref={this.state.description}
                    placeholder="Describe a tree"
                    aria-label="Describe a tree"
                    aria-describedby="basic-addon2"
                    />
                    <InputGroup.Append>
                    <Button variant="outline-secondary" onClick={this.buildTree}>Go</Button>
                    </InputGroup.Append>
                </InputGroup>
            </Container>
        );
    }
}

export default TreeOperations;