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
            treesStrs : props.treesStrs,
            reference : React.createRef(),
            description : React.createRef()
        }
        this.triggerUpdate = props.triggerUpdate;
        this.isCalled = false;
        this.addToArray = this.addToArray.bind(this);
        this.removeFromArray = this.removeFromArray.bind(this);
        this.buildTree = this.buildTree.bind(this);
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
                        tmpTree.buildTreeMatrixCaller();
                        tmpTree.organizeTreeMatrix();
                        tmpTree.setTreeType(this.typeIdToTreeTypeName(this.props.treeChoice[0]));
                        tmpTree.setId(this.state.treesStrs.length);
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
                        tmpTree.buildTreeMatrixCaller();
                        tmpTree.organizeTreeMatrix();
                        tmpTree.setTreeType(this.typeIdToTreeTypeName(this.props.treeChoice[0]));
                        tmpTree.setId(this.state.treesStrs.length);
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