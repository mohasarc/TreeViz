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

        this.centerX = 0;
        this.centerY = 0;

        this.beingEnimated = false;
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

        var properties = { spaceLeftBound : 0 };
        this.shapeTree(this.root, 1, properties);
        this.width = properties.spaceLeftBound;
        this.treeRightBound = this.width;
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
        if (parent == null)
            this.root = node;
        else // Add the node to the parent
            parent.addChild(node);

        node.setParent(parent);
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
     */
    draw(p){
        // Draw the note
        if (this.note != ''){
            var noteWidth = this.note.length * 8;
            var noteHeight = 25;
            var positionLeft = 25;
            var positionTop = 25;
            var textSize = 15;

            noteWidth *= (1/this.scale);
            noteHeight *= (1/this.scale);
            positionLeft *= (1/this.scale);
            positionTop *= (1/this.scale);
            textSize *= (1/this.scale);

            // Draw circles
            p.rectMode(p.CENTER)
            p.fill('FFFFF');
            p.rect(positionLeft + noteWidth/2, positionTop, noteWidth, noteHeight, 20);

            // Draw the node's text
            // Identify the location
            var nodeCenterX = positionLeft + noteWidth/2;
            var nodeCenterY = positionTop + (noteHeight / 4);
            // Draw it
            p.fill(0);
            p.textAlign(p.CENTER);
            p.textSize(textSize);
            p.text(this.note, nodeCenterX, nodeCenterY);

            // restore the default size for the rest of the drawing
            p.textSize(12);
        }

        this.drawConnections(this.root, p, 0);
        this.drawNodes(this.root, p, 0);
        this.printed = true;
    }
    
    /**
     * Draws the connections between the nodes
     * @param {The current node being draws (used for the recursive call)} node 
     * @param {The P5 object} p 
     * @param {The level of the current node} curLevel 
     */
    drawConnections(node, p, curLevel){

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
     * Draws all the tree nodes as ovals on the canvas and add their texts
     * @param {The current node being draws (used for the recursive call)} node 
     * @param {The P5 object} p 
     * @param {The level of the current node} curLevel 
     */
    drawNodes(node, p, curLevel){
    
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

    // /**
    //  * Udates the tree nodes locations according to 
    //  * the new size of the canvas
    //  */
    // resize(width, newCenterY, putInView){
    //     if (isNaN(width))
    //         return;
        
    //     // this.latestCenterX = width/2;

    //     if (putInView)
    //         this.putInView(width/2, newCenterY)
    //     else
    //         this.center(width/2, newCenterY);
    // }

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
     * A wrapper for moveTreeRec
     * @param {The amount of change in X direction} xAmount 
     * @param {The amount of change in Y direction} yAmount 
     */
    moveTree(xAmount, yAmount){
        this.centerX += xAmount * (1 / this.scale);
        this.centerY += yAmount * (1 / this.scale);
        this.moveTreeRec(this.root, xAmount * 0.5 * (1 / this.scale), yAmount * 0.5 * (1 / this.scale));
    }

    /**
     * Puts the root of the tree in this specific location
     * @param {The x value of the center} theCenterX 
     * @param {The y value of the center} theCenterY 
     */
    center(){
        // Create the tree centered at (rootX, rootY)
        var properties = { spaceLeftBound : 0 };
        this.shapeTree(this.root, 1, properties);
        this.visitedMark = !this.visitedMark;   

        var xShamt = this.centerX * (1 / this.scale) - this.root.getX();
        var yShamt = this.centerY - this.root.getY();

        this.moveTreeRec(this.root, xShamt, yShamt);
    }

    // putInView(theCenterX, theCenterY){
    //     // Update the center position
    //     // this.latestCenterX = theCenterX;

    //     var properties = { spaceLeftBound : 0 };

    //     // Take initial values for right and left bounds of the tree
    //     this.treeRightBound = this.root.getX();
    //     this.treeLeftBound = this.root.getX();

    //     // Create the tree centered at (rootX, rootY)
    //     this.shapeTree(this.root, 1, properties);
    //     this.visitedMark = !this.visitedMark;

    //     // Calculate the distance between (rootX and the target X, rootY and the target Y)
    //     var xShamt = theCenterX * (1/this.scale) - (this.treeRightBound - this.treeLeftBound) / 2;
    //     var yShamt = theCenterY * (1/this.scale) - 40 - this.root.getY();

    //     // putting bounds to center to be able to compare them with other nodes locations
    //     this.treeRightBound = this.root.getX();
    //     this.treeLeftBound = this.root.getX();
    //     this.moveTreeRec(this.root, xShamt, yShamt);
    // }

    /**
     * Shapes the tree accoding to the destance given in the
     * constants of the class
     * @param {The node being processed} curNode 
     * @param {The current level of the node} level 
     * @param {An object carrying the value of the right bound so far} properties 
     */
    shapeTree(curNode, level, properties){
        // updating the tree's height
        if (level > this.height)
            this.height = level;

        // Go through the left children if they exist
        var leftChildren = curNode.getLeftChildren();
        if (leftChildren){
            leftChildren.map(child=>{
                this.shapeTree(child, level + 1, properties);
            });
        }

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
        var xValue = leftBoundBeforeMid + this.NODE_SEPARATION + width/2;

        // IF NOT VISITED BEFORE
        // Assign X-value for current node and mark as visited
        // Assign X-value for middle child node and mark as visited
        if (curNode.isVisited() != this.visitedMark){
            curNode.setX(xValue);
            curNode.setY(level*40);
            curNode.visited(this.visitedMark);
        }

        // Go through the right children if they exist
        var rightChildren = curNode.getRightChildren();
        if (rightChildren){
            rightChildren.map(child=>{
                this.shapeTree(child, level + 1, properties);
            });
        }
    }

    /**
     * Moves all tree nodes in the direction of the
     * change in x and y value
     * @param {The node being processed} curNode 
     * @param {The change in X value} xShamt 
     * @param {The change in Y value} yShamt 
     */
    moveTreeRec(curNode, xShamt, yShamt){
        // shift self
        curNode.setX(curNode.getX() + xShamt);
        curNode.setY(curNode.getY() + yShamt);

        // visit all children and shift
        curNode.getChildren().map(child=>{
            this.moveTreeRec(child, xShamt, yShamt);
        });
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

    setId(id){
        this.id = id;
    }

    getId(){
        return this.id;
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

    setCenterX(centerX){
        this.centerX = centerX;
    }

    setCenterY(centerY){
        this.centerY = centerY;
    }

    getCenterX(){
        return this.centerX;
    }

    getCenterY(){
        return this.centerY;
    }
}

export default GenericTree;