import Node from './GenericNode'
import GenericNode from './GenericNode';

class GenericTree{
    /**
     * Empty constructor
     */
    constructor(){
        this.root = null;
        this.numLevels = 1;
        this.height = 1;
        this.width = 0;
        this.latest = [];
        this.levelsNodes = {};
        this.treeMatrix = [];
        this.criticalLevelNodesNum = 0;
        this.treeString = '';
        // for testing
        this.printed = false;
        this.spaceLeftBound = 0;
        this.NODE_SEPARATION = 3;
        this.visitedMark = true;
        this.treeLeftBound = 0;
        this.treeRightBound = 0;

        this.sequence = '';
        this.preferences = {};
        this.steps = [];

        this.latestCenterX = 0;
        this.note = '';
    }

    /**
     * Returns the tree string
     */
    getTreeString(){
        return this.treeString;
    }

    /**
     * Builds a tree according to its tree string
     * @param {The tree string of the desired tree} treeString 
     */
    construct(treeString){      
        var treeStack = [];
        var parentsStack = [];
        // clear the previous tree
        this.root = null;
        this.treeString = treeString;

        treeString.split('').map((char, i) => {
            switch (char) {
                case '{':
                    var tmpNode = new GenericNode(treeString.substring(i, treeString.length));
                    if (this.isEmpty()){
                        this.insert(tmpNode, null);
                    } else {
                        this.insert(tmpNode, parentsStack[parentsStack.length - 1]);
                    }

                    // Update stacks
                    treeStack.push(char);
                    parentsStack.push(tmpNode);
                    break;
                
                case '}':
                    treeStack.pop();
                    // if the node has no children, pop it
                    // from parents
                    if (treeString[i+1] != '(')
                        parentsStack.pop();
                    break;

                case '(':
                    treeStack.push(char);
                    break;

                case ',':
                    break;

                case ')':
                    // A node has finished so pop it from parents
                    treeStack.pop();
                    parentsStack.pop();
                    break;

                default:
                    break;
            }
        });
    }

    /**
     * assesses whether the tree is empty
     */
    isEmpty(){
        return this.root == null;
    }

    /**
     * inserts an item to the tree by adding it to its parent
     * given that its parent is already an item of the tree,
     * if father is NULL the child will be the root of the tree
     * @param {The child node} node 
     * @param {The parent of the child node} parent 
     */
    insert(node, parent) {
        // IF the tree is already empty
        if (parent == null){
            this.root = node;
        }
        else
            parent.addChild(node);

        node.setParent(parent);
        // this.criticalLevelNodesNum = this.criticalLevelNodes();

        var properties = {
            spaceLeftBound : 0
        };
        this.shapeTree(this.root, 1, properties);
        this.width = properties.spaceLeftBound;
        this.treeRightBound = this.width;
        // this.updateHeight(this.root, 1);
        // this.updateNumLevels();
    }

    /**
     * Traverses the tree items in inorder traversal
     * and condole logs all of them
     * @param {NOT USED CAN BE SET ANYTHING} p 
     * @param {NOT USED CAN BE SET ANYTHING} width 
     */
    traverse(p, width){
        // this.root.setX(width/2);
        this.traverseRec(this.root, p, 0);
    }

    /**
     * The recursive traverse methid..
     * traverses the tree items in inorder traversal
     * and condole logs all of them
     * @param {The current node for the recursive call} node
     * @param {NOT USED CAN BE SET ANYTHING} p 
     * @param {NOT USED CAN BE SET ANYTHING} width 
     */
    traverseRec(node, p, curLevel) {
        if (node == null)
            return;      
        else {
            // print self
            var spacebefore = ' ';
            for (let i = 0; i < curLevel; i++)
                spacebefore += '\t';
            // console.log(spacebefore, node.getValue());

            for (let i = 0; i < node.getChildren().length; i++){
                this.traverseRec(node.getChildren()[i], p, curLevel + 1);
            }
        }
    }

    /**
     * Draws the tree nodes on the canvas
     * @param {P5 object} p 
     * @param {The width of the canvas} width 
     */
    draw(p, width){
        if (this.root != null){
            // this.root.setX(width/2);
            // this.root.setY(40);
        }

        // Draw the note
        if (this.note != ''){
            var width = this.note.length * 7;
            // Draw circles
            p.rectMode(p.CENTER)
            p.fill('FFFFF');
            p.rect(25 + width/2, 25, width, 25, 20);

            // Draw the node's text
            // Identify the location
            var nodeCenterX = 25 + width/2;
            var nodeCenterY = 30;
            // Draw it
            p.fill(0);
            p.textAlign(p.CENTER);
            p.text(this.note, nodeCenterX, nodeCenterY);
        }

        this.drawConnections(this.root, p, 0);
        // console.log('drawing the tree');
        this.drawNodes(this.root, p, 0);
        this.printed = true;
    }

    /**
     * Draws all the tree nodes as ovals on the canvas and add their texts
     * @param {The current node being draws (used for the recursive call)} node 
     * @param {The P5 object} p 
     * @param {The level of the current node} curLevel 
     */
    drawNodes(node, p, curLevel){
    const X_SPACING = 10;

        if (node == null)
            return;
        else {
            // Update the level
            var childrenLevel = curLevel + 1;

            // draw current node
            node.draw(p);

            // draw all its children
            node.getChildren().map((child, i) => {
                // calculate the location of the child
                var childrenNum = node.getChildren().length;
                var curLevelNodesNum = this.levelsNodes[childrenLevel];
                // var childX = this.calculateX(childrenNum, curLevelNodesNum, i);
                var childY = node.getY() + 40;

                // update the child's location
                if (!this.printed)
                    // console.log('the location', childX);
                // child.setX(childX);
                child.setY(childY);
                this.drawNodes(child, p, childrenLevel);
            });
        }
    }
    
    /**
     * Draws the connections between the nodes
     * @param {The current node being draws (used for the recursive call)} node 
     * @param {The P5 object} p 
     * @param {The level of the current node} curLevel 
     */
    drawConnections(node, p, curLevel){
        const X_SPACING = 10;
    
            if (node == null)
                return;
            else {
                // Update the level
                var childrenLevel = curLevel + 1;
    
                // draw all its children
                node.getChildren().map((child, i) => {
                    // calculate the location of the child
                    var childrenNum = node.getChildren().length;
                    var curLevelNodesNum = this.levelsNodes[childrenLevel];
                    // var childX = this.calculateX(childrenNum, curLevelNodesNum, i);
                    var childY = node.getY() + 40;
    
                    // update the child's location
                    if (!this.printed)
                        // console.log('the location', childX);

                    // child.setX(childX);
                    child.setY(childY);

                    // draw the line if child is not empty
                    if (!child.isEmpty()){
                        p.stroke(255);
                        p.line(node.getX(), node.getY(), child.getX(), child.getY());
                    }

                    this.drawConnections(child, p, childrenLevel);
                });
            }
        }

    /**
     * Udates the tree nodes locations according to 
     * the new size of the canvas
     */
    resize(width, putInView){
        if (isNaN(width))
            return;
        
        // this.latestCenterX = width/2;

        if (putInView)
            this.putInView(width/2)
        else
            this.center(width/2);
    }

    /**
     * Returns the tree height in pixels
     */
    getHeight(){
        return (this.height * 45 + 10) * this.scale;
    }

    /**
     * Returns the tree width in pixels
     */
    getWidth(){
        return this.width * this.scale;
    }

    /**
     * 
     * @param {The type of the tree} treeType 
     */
    setTreeType(treeType){
        this.treeType = treeType;
    }

    /**
     * 
     */
    getTreeType(){
        return this.treeType;
    }

    moveTree(xAmount, yAmount){
        // putting bounds to center to be able to compare them with other nodes locations
        this.treeLeftBound = this.root.getX();
        this.treeRightBound = this.root.getX();
        // Update the latest center x value
        this.latestCenterX = xAmount * 0.5 * (1 / this.scale);
        this.moveTreeRec(this.root, xAmount * 0.5 * (1 / this.scale), yAmount * 0.5 * (1 / this.scale));
    }

    setId(id){
        this.id = id;
    }

    getId(){
        return this.id;
    }

    center(theCenterX){
        // Update the center position
        // this.latestCenterX = theCenterX;

        var properties = {
            spaceLeftBound : 0
        };
        this.shapeTree(this.root, 1, properties);
        this.visitedMark = !this.visitedMark;
        var xShamt = (theCenterX) * (1 / this.scale) - this.root.getX();
        var yShamt = 40 - this.root.getY();

        // putting bounds to center to be able to compare them with other nodes locations
        this.treeLeftBound = this.root.getX();
        this.treeRightBound = this.root.getX();
        this.moveTreeRec(this.root, xShamt, yShamt);
    }

    putInView(theCenterX){
        // Update the center position
        // this.latestCenterX = theCenterX;

        var properties = {
            spaceLeftBound : 0
        };

        this.treeRightBound = this.root.getX();
        this.treeLeftBound = this.root.getX();
        this.shapeTree(this.root, 1, properties);
        this.visitedMark = !this.visitedMark;

        var xShamt = theCenterX * (1/this.scale) - (this.treeRightBound - this.treeLeftBound) / 2;
        var yShamt = 40 - this.root.getY();

        // putting bounds to center to be able to compare them with other nodes locations
        this.treeRightBound = this.root.getX();
        this.treeLeftBound = this.root.getX();
        this.moveTreeRec(this.root, xShamt, yShamt);
    }

    shapeTree(curNode, level, properties){
        // updating the tree's height
        if (level > this.height)
            this.height = level;

        // Go through the left children if they exist
        var leftChildren = curNode.getLeftChildren();
        if (leftChildren)
            leftChildren.map(child=>{
                this.shapeTree(child, level + 1, properties);
            });


        // Visit the middle child
        var middleChild = curNode.getMiddleChild();
        var leftBoundBeforeMid = properties.spaceLeftBound;
        if (middleChild)
            this.shapeTree(middleChild, level + 1, properties)
        else // only update the space left bound
            properties.spaceLeftBound = properties.spaceLeftBound + this.NODE_SEPARATION + curNode.getWidth();

        var leftBoundAfterMid = properties.spaceLeftBound;
        var width = leftBoundAfterMid - leftBoundBeforeMid;

        // calculate X-value for current node using width from
        // max(currentNodeWidth, middleSubTreeWidth)
        var xValue =leftBoundBeforeMid + this.NODE_SEPARATION + width/2;

        // IF NOT VISITED BEFORE
        // Assign X-value for current node and mark as visited
        // Assign X-value for middle child node and mark as visited
        if (curNode.isVisited() != this.visitedMark){
            curNode.setX(xValue);
            curNode.setY(level*40);
            curNode.visited(this.visitedMark);
            
            // Updating the tree bounds
            if (xValue > this.treeRightBound)
                this.treeRightBound = xValue;
            if (xValue < this.treeLeftBound)
                this.treeLeftBound = xValue;
        }

        // Go through the right children if they exist
        var rightChildren = curNode.getRightChildren();
        if (rightChildren)
            rightChildren.map(child=>{
                this.shapeTree(child, level + 1, properties);
            });
    }

    moveTreeRec(curNode, xShamt, yShamt){
        // shift self
        curNode.setX(curNode.getX() + xShamt);
        curNode.setY(curNode.getY() + yShamt);

        // Update the bounds location
        if (curNode.getX() > this.treeRightBound)
            this.treeRightBound = curNode.getX();
        if (curNode.getX() < this.treeLeftBound)
            this.treeLeftBound = curNode.getX();

        // visit all children and shift
        curNode.getChildren().map(child=>{
            this.moveTreeRec(child, xShamt, yShamt);
        });
    }

    setScale(scale){
        this.scale = scale;
    }

    getScale(){
        return this.scale;
    }
    
    setTreeSequence(sequence){
        this.sequence = sequence;
    }

    getTreeSequence(){
        return this.sequence;
    }

    setPreferences(preferences){
        this.preferences = preferences;
    }

    getPreferences(){
        return this.preferences;
    }

    setSteps(steps){
        this.steps = steps;
    }

    getSteps(){
        return this.steps;
    }

    setNote(note){
        this.note = note;
    }

    getNote(){
        return this.note;
    }
}

export default GenericTree;