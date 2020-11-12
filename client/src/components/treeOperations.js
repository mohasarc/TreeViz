import React from 'react'
import Button from 'react-bootstrap/Button'
import Container from 'react-bootstrap/Container'
import GenericTree from '../models/GenericTree'
import FormControl from 'react-bootstrap/FormControl'
import InputGroup from 'react-bootstrap/InputGroup'
import Row from 'react-bootstrap/Row'
import Col from 'react-bootstrap/Col'
import axios from 'axios'
import { withSnackbar } from 'notistack';
import XRegExp from 'xregexp'
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
        this.usedLatest = '';
    }

    performOperation = (e, operationValue) => {
        // Local variables
        const emptiness = /^\s*$/;
        var operation;

        // get the operation required
        if (typeof e.target.attributes.operation != 'undefined')
            operation = e.target.attributes.operation.value;
        else 
            operation = operationValue;

        this.usedLatest = operation;
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
                if (operationObj.treeContent.treeSequence == '' && operationObj.treeContent.treeString == ''){
                    operationObj.operation.type = 'build';
                    operationObj.treeContent.treeSequence = operationObj.operation.value;
                } else {
                    operationObj.operation.type = 'insert';
                }

                if (emptiness.test(operationObj.operation.value) || !Number.isInteger(+operationObj.operation.value)){
                    if (emptiness.test(operationObj.operation.value))
                        this.props.enqueueSnackbar(`Please enter a value first`, {variant: 'warning'});
                    if (!Number.isInteger(+operationObj.operation.value))
                        this.props.enqueueSnackbar(`The value should be integer`, {variant: 'error'});
                    return;
                }
            break;
    
            case 'remove':
                operationObj.operation.type = 'remove';

                if (emptiness.test(operationObj.operation.value) || !Number.isInteger(+operationObj.operation.value)){
                    if (emptiness.test(operationObj.operation.value))
                        this.props.enqueueSnackbar(`Please enter a value first`, {variant: 'warning'});
                    if (!Number.isInteger(+operationObj.operation.value))
                        this.props.enqueueSnackbar(`The value should be integer`, {variant: 'error'});
                    return;
                }
            break;
    
            case 'build':
                var description = this.state.description.current.value;
                var delimIndex = description.indexOf(':');
                const re = /^(d?-?\d+,?)+/;
                var str1, str2, treeString, treeSequence;

                if (delimIndex > 0){
                    str1 = description.substr(0, delimIndex);
                    str2 = description.substr(delimIndex + 1);
                } else {
                    str1 = description;
                }

                if (re.test(str1)){
                    treeSequence = str1;
                    treeString = str2;
                } else {
                    treeSequence = str2;
                    treeString = str1;
                }

                operationObj.treeContent.treeString = treeString;
                operationObj.treeContent.treeSequence = treeSequence;
                operationObj.operation.type = 'build';

                if (emptiness.test(description)){
                    this.props.enqueueSnackbar(`Please write a tree description first`, {variant: 'warning'});
                    return;
                }
            break;
    
            case 'buildRandom':
                operationObj.treeContent.treeString = '';
                operationObj.treeContent.treeSequence = '';
                operationObj.operation.preferences.range.min = this.state.rangeMin.current.value;
                operationObj.operation.preferences.range.max = this.state.rangeMax.current.value;
                operationObj.operation.preferences.numNodes = this.state.numNodes.current.value;

                operationObj.operation.type = 'buildRandom';

                if (emptiness.test(operationObj.operation.preferences.range.min) || 
                    emptiness.test(operationObj.operation.preferences.range.max) || 
                    emptiness.test(operationObj.operation.preferences.numNodes) ||
                    !Number.isInteger(+operationObj.operation.preferences.range.min) ||
                    !Number.isInteger(+operationObj.operation.preferences.range.max) ||
                    !Number.isInteger(+operationObj.operation.preferences.numNodes)){
                        if (emptiness.test(operationObj.operation.preferences.range.min))
                            this.props.enqueueSnackbar(`Please specify the minimum value a key can get`, {variant: 'warning'});

                        if (!Number.isInteger(+operationObj.operation.preferences.range.min))
                            this.props.enqueueSnackbar(`The minimum value needs to be integer`, {variant: 'error'});

                        if (emptiness.test(operationObj.operation.preferences.range.max))
                            this.props.enqueueSnackbar(`Please specify the maximum value a key can get`, {variant: 'warning'});

                        if (!Number.isInteger(+operationObj.operation.preferences.range.max))
                            this.props.enqueueSnackbar(`The maximum value needs to be integer`, {variant: 'error'});

                        if (emptiness.test(operationObj.operation.preferences.numNodes))
                            this.props.enqueueSnackbar(`Please specify the number of nodes wanted`, {variant: 'warning'});

                        if (!Number.isInteger(+operationObj.operation.preferences.numNodes))
                            this.props.enqueueSnackbar(`The number of nodes needs to be integer`, {variant: 'error'});
    
                        return;
                    }

                    if (operationObj.operation.preferences.range.max < operationObj.operation.preferences.range.min){
                        this.props.enqueueSnackbar('The maximum value of the range cannot be less than the minimum', {variant: 'error'});
                        return;
                    }

                    if (operationObj.operation.preferences.range.max - operationObj.operation.preferences.range.min + 1 < operationObj.operation.preferences.numNodes){
                        this.props.enqueueSnackbar(`The range specified cannot fit ` + operationObj.operation.preferences.numNodes + ' keys.', {variant: 'info'});
                        this.props.enqueueSnackbar('Therefore a tree of ' + (operationObj.operation.preferences.range.max - operationObj.operation.preferences.range.min + 1) + ' keys is created.', {variant: 'info'});
                    }
            break;
    
            default:
            break;
        }

        if (!this.isCalled){
            axios.post('/api/trees/performOperation', operationObj).then((response) => {
                // Processing data came from backend
                var responseObj = response.data;

                if (responseObj){
                    // If treeString is empty // tree is empty
                    if (responseObj.status == 'fail'){
                        this.props.enqueueSnackbar(responseObj.message, {variant: 'error', 'horizontal': 'right', 'vertical': 'bottom'});
                    } else if (responseObj.treeString == ''){
                        this.props.enqueueSnackbar('Tree is empty', {variant: 'error', 'horizontal': 'right', 'vertical': 'bottom'});
                    } else {
                        if (responseObj.status == 'warning'){
                            this.props.enqueueSnackbar(responseObj.message, {variant: 'warning'});
                        }

                        // create and add the tree read into the trees array
                        var tmpTree = new GenericTree();
                        tmpTree.construct(responseObj.treeString);
                        tmpTree.setTreeSequence(responseObj.treeSequence);

                        tmpTree.setPreferences(responseObj.preferences);
                        tmpTree.setSteps(responseObj.steps);
                        tmpTree.setTreeType(responseObj.type);
                        tmpTree.setScale(1);
                        tmpTree.setNewlyAdded(true);

                        // calculate the tree id and set it
                        if (this.state.trees.length == 0){
                            tmpTree.setId(1);
                        } else {
                            tmpTree.setId(this.state.trees[0].getId() + 1);
                        }

                        // Add the tree to trees aray
                        this.state.trees.unshift(tmpTree);
                        this.triggerUpdate();
                    }
                }
            }).catch((error) => {this.props.enqueueSnackbar('Server error :' + error, {variant: 'error', anchorOrigin : { 'horizontal': 'center', 'vertical': 'bottom' }})});

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

    handleInputEnter = (e) => {
        e.preventDefault();
        if (e.keyCode === 13){
            if (this.usedLatest === 'insert'){
                this.performOperation(e, 'insert')
            } else if (this.usedLatest === 'remove') {
                this.performOperation(e, 'remove');
            }
        }
    }

    render(){
        return (
                <Row xs={12} md={12} lg={12}>
                    <Col xs={12} md={6} lg={7}>
                        <InputGroup className="mb-3">
                            <FormControl
                            ref={this.state.reference}
                            placeholder="Enter a value"
                            aria-label="Enter a value"
                            aria-describedby="basic-addon2"
                            onKeyUp={this.handleInputEnter}
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
                            operation='build'
                            onKeyUp={(e) => { if (e.keyCode == 13) this.performOperation(e) }}
                            />
                            <InputGroup.Append>
                                <Button operation='build' variant="outline-secondary" onClick={this.performOperation}>Go</Button>
                            </InputGroup.Append>
                        </InputGroup>
                    </Col>
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
                                <Button operation='buildRandom' variant="outline-secondary" onClick={this.performOperation}>Generate</Button>
                            </InputGroup.Prepend>
                        </InputGroup>
                    </Col>
                </Row>
        );
    }
}

export default withSnackbar(TreeOperations);