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
        this.addToArray = this.addToArray.bind(this);
        this.removeFromArray = this.removeFromArray.bind(this);
        this.buildTree = this.buildTree.bind(this);
        this.buildRandonTree = this.buildRandonTree.bind(this);
        this.minChanged = this.minChanged.bind(this);
        this.maxChanged = this.maxChanged.bind(this);
        this.numNodesChanged = this.numNodesChanged.bind(this);
        this.counter = 0;
    }

    addToArray(e){
        this.setState(state => {
            if (!this.isCalled){
                // this.state.tree.insert(this.state.reference.current.value);
                var curTreeStrings;
                this.state.treesStrs.length >= 1 
                ? curTreeStrings = this.state.treesStrs[this.state.treesStrs.length-1]
                : curTreeStrings = '';

                axios.post('/api/trees/addValue', {value : this.state.reference.current.value,
                                         treeStrings : curTreeStrings
                                        }
                            ).then((response) => {
                    // Processing data came from backend
                    var treeStrings = response.data.treeStrings;
                    if (treeStrings){
                        // add the tree strings into the treeStr array
                        this.state.treesStrs.push(treeStrings);
                        // pop a tree from trees
                        // if (this.state.trees.length > 1)
                        //     this.state.trees.pop();

                        // add the tree read into the trees array
                        var tmpTree = new GenericTree();
                        tmpTree.construct(treeStrings[this.props.treeChoice[0]]);
                        // tmpTree.buildTreeMatrixCaller();
                        // tmpTree.organizeTreeMatrix();
                        tmpTree.setTreeType(this.typeIdToTreeTypeName(this.props.treeChoice[0]));
                        tmpTree.setId(this.state.treesStrs.length);
                        tmpTree.setScale(1);
                        this.state.trees.unshift(tmpTree);

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
            // console.log('remove called', this.state.reference.current.value);
            // return {};
        })
    }

    buildTree(e){   
        this.setState((prevState)=>{
            if (!this.isCalled){
                axios.post('/api/trees/sendTree', {treeString : this.state.description.current.value,
                                                   treeChoice : this.props.treeChoice[0]}).then((response) => {
                    // Processing data came from backend
                    var treeStrings = response.data.treeStrings;
                    if (treeStrings){
                        // add the tree strings into the treeStr array
                        this.state.treesStrs.push(treeStrings);
                        // pop a tree from trees
                        // if (this.state.trees.length > 1)
                        //     this.state.trees.pop();

                        // add the tree read into the trees array
                        var tmpTree = new GenericTree();
                        tmpTree.construct(treeStrings[this.props.treeChoice[0]]);
                        // tmpTree.buildTreeMatrixCaller();
                        // tmpTree.organizeTreeMatrix();
                        tmpTree.setTreeType(this.typeIdToTreeTypeName(this.props.treeChoice[0]));
                        tmpTree.setId(this.state.treesStrs.length);
                        tmpTree.setScale(1);
                        this.state.trees.unshift(tmpTree);

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

    buildRandonTree(e){
        this.setState(state => {
            if (!this.isCalled){

                axios.post('/api/trees/buildRandomTree', {range: {min : this.state.rangeMin.current.value, 
                                                                  max : this.state.rangeMax.current.value},
                                                          numNodes : this.state.numNodes.current.value
                                                        }
                            ).then((response) => {
                    // Processing data came from backend
                    var treeStrings = response.data.treeStrings;
                    if (treeStrings){
                        // add the tree strings into the treeStr array
                        this.state.treesStrs.push(treeStrings);
                        // pop a tree from trees
                        // if (this.state.trees.length > 1)
                        //     this.state.trees.pop();

                        // add the tree read into the trees array
                        var tmpTree = new GenericTree();
                        tmpTree.construct(treeStrings[this.props.treeChoice[0]]);
                        // tmpTree.buildTreeMatrixCaller();
                        // tmpTree.organizeTreeMatrix();
                        tmpTree.setTreeType(this.typeIdToTreeTypeName(this.props.treeChoice[0]));
                        tmpTree.setId(this.state.treesStrs.length);
                        tmpTree.setScale(1);
                        this.state.trees.unshift(tmpTree);

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

    performOperation = (e) => {
        // get the operation required
        var operation = e.target.attributes.operation.value;
        var operationObj = {
            'treeContent' : {
                            'treeString' : this.state.trees.length > 0? this.state.trees[0].getTreeString() : '',
                            'treeSequence' : this.state.trees.length > 0? this.state.trees[0].getTreeSequence() : '',
                            },
            'targetTreeInfo' : {
                                'type' : this.props.treeChoice[0],
                                'preferences' : {
                                    'order' : 3,
                                },
                               },
            'operation' : {
                            'type' : '',
                            'value' : this.state.reference.current.value,
                            'preferences' : {},
                          }
        }

        switch (operation) {
            case 'insert':               
                operationObj.operation.type = 'insert';
            break;
    
            case 'remove':
                operationObj.operation.type = 'remove';
            break;
    
            case 'build':
                operationObj.operation.type = 'build';
            break;
    
            case 'buildRandom':
                operationObj.treeContent.treeString = '';
                operationObj.treeContent.treeSequence = '';
                operationObj.operation.type = 'buildRandom';
            break;
    
            default:
            break;
        }


        this.setState(state => {
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
                        this.state.trees.unshift(tmpTree);
                        tmpTree.setId(this.state.trees.length);

                        this.triggerUpdate();
                    }
                });

                this.isCalled = true;
            } else {
                this.isCalled = false;
            }
        });
        
        this.isCalled = false;
        console.log(e.target.attributes.operation);

        e.preventDefault();
    }

    typeIdToTreeTypeName(id){
        switch (id) {
            case 'binary':
                return 'Binary Tree';
            break;
            case '23':
                return '2-3 Tree';
            break;
            case '234':
                return '2-3-4 Tree';
            break;
            case 'avl':
                return 'AVL Tree';
            break;
            case 'redblack':
                return 'Red-Black Tree';
            break;

            default:
            break;
        }
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
            <Container>
                <Row xs={12} md={12} lg={12}>
                    <Col xs={12} md={6} lg={6}>
                        <InputGroup className="mb-3">
                            <FormControl
                            ref={this.state.reference}
                            placeholder="Enter a value"
                            aria-label="Enter a value"
                            aria-describedby="basic-addon2"
                            />
                            <InputGroup.Append>
                            <Button operation='insert' variant="outline-secondary" onClick={this.performOperation}>+</Button>
                            <Button operation='remove' variant="outline-secondary" onClick={this.removeFromArray}>-</Button>
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
                                <Button operation='build' variant="outline-secondary" onClick={this.buildTree}>Go</Button>
                            </InputGroup.Append>
                        </InputGroup>
                    </Col>
                    <Col xs={12} md={6} lg={6}>
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
                                <Button operation='buildRandom' variant="outline-secondary" onClick={this.buildRandonTree}>Create tree</Button>
                            </InputGroup.Prepend>
                        </InputGroup>
                    </Col>
                </Row>

            </Container>
        );
    }
}

export default TreeOperations;