import React from 'react'
import Button from 'react-bootstrap/Button'
import Container from 'react-bootstrap/Container'
import GenericTree from '../models/GenericTree'
import FormControl from 'react-bootstrap/FormControl'
import InputGroup from 'react-bootstrap/InputGroup'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import axios from 'axios'
import { unstable_batchedUpdates } from 'react-dom'

class TreeOperations extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            trees : props.trees,
            treesStrs : props.treesStrs,
            reference : React.createRef(),
            description : React.createRef(),
            rangeMin : React.createRef(),
            rangeMax : React.createRef(),
            numNodes : React.createRef(),
            defaultValues : {
                min : 5,
                max : 99,
                numNodes : 15,
            }
        }
        this.triggerUpdate = props.triggerUpdate;
        this.isCalled = false;
        this.minChanged = this.minChanged.bind(this);
        this.maxChanged = this.maxChanged.bind(this);
        this.numNodesChanged = this.numNodesChanged.bind(this);
        this.counter = 0;
    }

    performOperation = (e) => {
        // get the operation required
        var operation = e.target.attributes.operation.value;
        var operationObj = {
            'treeContent' : {
                            'treeString' : this.state.trees.length > 0? this.state.trees[0].getTreeString() : '',
                            'treeSequence' : this.state.trees.length > 0? this.state.trees[0].getTreeSequence() : '',
                            'type' : this.state.trees.length > 0? this.state.trees[0].getTreeType() : '',
                            },
            'targetTreeInfo' : {
                                'type' : this.props.preferences.type,
                                'preferences' : this.props.preferences,
                               },
            'operation' : {
                            'type' : '',
                            'value' : this.state.reference.current.value,
                            'preferences' : {
                                'range' : { 'min' : 0, 'max' : 0},
                                'numNodes' : 0, 
                            },
                          }
        }

        console.log('sending ', operationObj)

        switch (operation) {
            case 'insert':               
                operationObj.operation.type = 'insert';
            break;
    
            case 'remove':
                operationObj.operation.type = 'remove';
            break;
    
            case 'build':
                var description = this.state.description.current.value;
                var delimIndex = description.indexOf(':');
                var treeString = '';
                var treeSequence = '';

                if (delimIndex > 0){
                    treeString = description.substr(0, delimIndex);
                    treeSequence = description.substr(delimIndex + 1);
                } else {
                    treeString = description;
                    treeSequence = '';
                }

                operationObj.treeContent.treeString = treeString;
                operationObj.treeContent.treeSequence = treeSequence;
                operationObj.operation.type = 'build';
            break;
    
            case 'buildRandom':
                operationObj.treeContent.treeString = '';
                operationObj.treeContent.treeSequence = '';
                operationObj.operation.preferences.range.min = this.state.rangeMin.current.value;
                operationObj.operation.preferences.range.max = this.state.rangeMax.current.value;
                operationObj.operation.preferences.numNodes = this.state.numNodes.current.value;

                operationObj.operation.type = 'buildRandom';
            break;
    
            default:
            break;
        }

        if (!this.isCalled){
            axios.post('/api/trees/performOperation', operationObj).then((response) => {
                // Processing data came from backend
                var responseObj = response.data;

                if (responseObj){
                    // add the tree read into the trees array
                    var tmpTree = new GenericTree();
                    tmpTree.construct(responseObj.treeString);
                    tmpTree.setTreeSequence(responseObj.treeSequence);
                    tmpTree.setPreferences(responseObj.preferences);

                    tmpTree.setTreeType(responseObj.type);
                    tmpTree.setScale(1);
                    if (this.state.trees.length == 0){
                        tmpTree.setId(1);
                    } else {
                        tmpTree.setId(this.state.trees[0].getId() + 1);
                    }
                    this.state.trees.unshift(tmpTree);
                    tmpTree.setSteps(responseObj.steps);

                    this.triggerUpdate();
                }
            });

            this.isCalled = true;
        } else {
            this.isCalled = false;
        }
        
        this.isCalled = false;
        e.preventDefault();
    }

    setTreeDescription(description){
        this.state.description.current.value = description;
    }

    
    maxChanged(value){
        this.setState({
            defaultValues : {
                max : value
            }
        });
    }

    minChanged(value){
        this.setState({
            defaultValues : {
                min : value
            }
        });
    }

    numNodesChanged(value){
        this.setState({
            defaultValues : {
                numNodes : value
            }
        });
    }
    

    render(){
        return (
                <Row xs={12} md={12} lg={12}>
                    <Col xs={12} md={6} lg={5}>
                        <InputGroup className="mb-3" size='sm' style={{'margin-top':'0.5em'}}>
                            <InputGroup.Prepend>
                                <InputGroup.Text>Values range</InputGroup.Text>
                            </InputGroup.Prepend>
                            <FormControl
                            ref={this.state.rangeMin}
                            placeholder="min"
                            aria-label="min"
                            value={this.state.defaultValues.min}
                            onChange={e=>this.minChanged(e.target.value)}
                            aria-describedby="basic-addon2"
                            />
                            <FormControl
                            ref={this.state.rangeMax}
                            placeholder="max"
                            aria-label="max"
                            value={this.state.defaultValues.max}
                            onChange={e=>this.maxChanged(e.target.value)}
                            aria-describedby="basic-addon2"
                            />
                        </InputGroup>
                        <InputGroup className="mb-3" size='sm'>
                            <InputGroup.Prepend>
                                <InputGroup.Text>Nodes count</InputGroup.Text>
                            </InputGroup.Prepend>
                            <FormControl
                            ref={this.state.numNodes}
                            placeholder="number of nodes"
                            aria-label="number of nodes"
                            value={this.state.defaultValues.numNodes}
                            onChange={e=>this.numNodesChanged(e.target.value)}
                            aria-describedby="basic-addon2"
                            />
                            <InputGroup.Prepend>
                                <Button operation='buildRandom' variant="outline-secondary" onClick={this.performOperation}>Create tree</Button>
                            </InputGroup.Prepend>
                        </InputGroup>
                    </Col>
                    <Col xs={12} md={6} lg={7}>
                        <InputGroup className="mb-3">
                            <FormControl
                            ref={this.state.reference}
                            placeholder="Enter a value"
                            aria-label="Enter a value"
                            aria-describedby="basic-addon2"
                            />
                            <InputGroup.Append>
                            <Button operation='insert' variant="outline-secondary" onClick={this.performOperation}>+</Button>
                            <Button operation='remove' variant="outline-secondary" onClick={this.performOperation}>-</Button>
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
                                <Button operation='build' variant="outline-secondary" onClick={this.performOperation}>Go</Button>
                            </InputGroup.Append>
                        </InputGroup>
                    </Col>
                </Row>
        );
    }
}

export default TreeOperations;