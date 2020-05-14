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
        this.latest = [];
        this.levelsNodes = {};
        this.treeMatrix = [];
        this.criticalLevelNodesNum = 0;
        this.treeString = '';
        // for testing
        this.printed = false;
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
        this.criticalLevelNodesNum = this.criticalLevelNodes();
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
            console.log(spacebefore, node.getValue());

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
            this.root.setY(40);
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
                var childX = this.calculateX(childrenNum, curLevelNodesNum, i);
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
                    var childX = this.calculateX(childrenNum, curLevelNodesNum, i);
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
     * PROBABLY NOT USED /// ****** CHECK IT LATER *******
     * @param {*} childrenNum 
     * @param {*} curLevelNodesNum 
     * @param {*} i 
     */
    calculateX(childrenNum, curLevelNodesNum, i){
        const X_SPACING = 10;
        return (((i - childrenNum/2)*this.criticalLevelNodesNum/(2*curLevelNodesNum)) * X_SPACING + this.root.getX());
    }

    /**
     * Calculates the level with the largest number of nodes.
     * called critical since it is the level that might have 
     * clashes between its nodes
     */
    criticalLevelIndex(){
        this.levelsNodes = {};
        this.updateCriticalLevel(this.root, 1);
        var maxLevel = 0;
        var maxLevelIndex = 0;

        for (let level in this.levelsNodes){
            if (this.levelsNodes[level] > maxLevel){
                maxLevel = this.levelsNodes[level];
                maxLevelIndex = level;
            }
        }

        return maxLevelIndex;
    }

    /**
     * Calculates the number of nodes in the critical level
     */
    criticalLevelNodes(){
        this.levelsNodes = {};
        this.updateCriticalLevel(this.root, 1);
        var maxLevel = 0;
        
        for (let level in this.levelsNodes){
            if (this.levelsNodes[level] > maxLevel)
                maxLevel = this.levelsNodes[level];
        }

        return maxLevel;
    }

    // CANT REMEMBER **** MAYBE NOT USED ANYMORE!! ****
    updateCriticalLevel(node, curLevel) {
        // console.log('updating level ', curLevel);
        if (node == null)
            return;
        else {
            if (!(curLevel in this.levelsNodes)){
                this.levelsNodes[curLevel] = node.getChildren().length;
            } else {
                this.levelsNodes[curLevel] = this.levelsNodes[curLevel] + node.getChildren().length;
            }

            // console.log('kids num', node.getChildren().length);
            // console.log('the object', this.levelsNodes);

            for (let i = 0; i < node.getChildren().length; i++){
                this.updateCriticalLevel(node.getChildren()[i], curLevel + 1);
            }
        }
    }

    /**
     * Returns the tree height in pixels
     */
    getHeight(){
        let levelsCount = 0;
        for (let level in this.levelsNodes){
            if (level > levelsCount)
                levelsCount = level;
        }

        return parseInt(levelsCount) * 45 + 10;
    }

    /**
     * Calls the recursive method buildTreeMatrix
     */
    buildTreeMatrixCaller(){
        // console.log('callig with root', this.root);
        this.buildTreeMatrix(this.root, 0);
    }

    /**
     * Builds a matrix out of the tree that is each row is a levels 
     * and contains multiple nodes s.t. the nodes in that level
     * @param {The current node being processed (used for the recursive call)} node 
     * @param {The level of the curret node} level 
     */
    buildTreeMatrix(node, level){
        const multiple = 2;

        if (node == null)
            return;

        // add the current node to the matrix
        if (!this.treeMatrix[level]){
            this.treeMatrix[level] = new Array();
            node.setX(1);
            // console.log(node);
            this.treeMatrix[level].push(node);
        }
        else{
            node.setX(this.treeMatrix[level][this.treeMatrix[level].length - 1].getX() + 1);
            this.treeMatrix[level].push(node);
        }

        // go to children
        node.getChildren().map((child) => {
            this.buildTreeMatrix(child, level + 1);
        });
    }

    /**
     * This methods fits the nodes of the tree in suitable
     * locations so that no clashes can happen and all nodes
     * are visible. The method does change the X- values of the
     * nodes so that no two nodes on the same Y-axis have the
     * same X-value. On the other hand, children of a particular
     * node should be distributed below that node.
     * ***********************************************************
     * The algorithm starts at the critical level, fits everything 
     * bellow it in place by performing necessary shifts for the 
     * critical level nodes and the nodes in the levels below. Then
     * after everything below the critical level is in place, it 
     * will traverse the levels above and fit them al according to
     * the critical level after it was updated.
     * ***********************************************************
     */
    organizeTreeMatrix(){
        // for (let j = 0; j < this.treeMatrix.length; j++){
            // for (let i = 1; i < this.treeMatrix[2].length; i++){
            //     // this.treeMatrix[2][i].setX(this.treeMatrix[2][i].getX() * 200);
            // }
        // }


        // console.log('the updated matrix', this.treeMatrix);

        var XNodes = this.criticalLevelNodes();
        var CLI = parseInt(this.criticalLevelIndex());
        var firstInsertedChild;
        var childrenGroup;
        var shamt;
        // console.log('organise matrix called and cli = ', CLI );

        // Starting from the level after critical level, iterating until the last level
        this.fitCLChildren(CLI, this.treeMatrix);

        // starting from the level before CLI level goint all the way up to the root
        this.fitCLParents(CLI, this.treeMatrix);
    }

    /**
     * Fits the nodes bellow the critical level in place
     * @param {The index of the critical level s.t. the tree matrix row index} CLI 
     * @param {The tree matrix} matrix 
     */
    fitCLChildren(CLI , matrix){
        // Local variables
        var childrenGroup = [];
        var firstChildOfGroup = 0;
        var avgChildLoc = 0;
        var shamt = 0;

        // The Code
        for (let level = CLI + 1; level < matrix.length; level++){
            // Go through the children of a level after CL
            matrix[level].map((child, i) => {
                if (childrenGroup.length == 0 || child.getParent() == childrenGroup[0].getParent()){
                    // Remember the first inserted child's index
                    if (childrenGroup.length == 0)
                        firstChildOfGroup = i;

                    // Add the child to the group
                    childrenGroup.push(child);
                }

                // If node belonge to a different group or is the last node in level
                if (child.getParent() != childrenGroup[0].getParent() || i == (matrix[level].length - 1)) {
                    avgChildLoc = this.findAvgLocation(childrenGroup);

                    // Process the data (do necessary shifts)
                    if (avgChildLoc < childrenGroup[0].getParent().getX()){
                        // shift this children group nodes and all nodes
                        // that come after them to the right

                        // Calculate the shift amount and shift
                        shamt = childrenGroup[0].getParent().getX() - avgChildLoc;
                        this.shiftSubRow(matrix, firstChildOfGroup, level, shamt);

                    } else {
                        // shift all nodes after parent column and before
                        // parent level
                        shamt = avgChildLoc - childrenGroup[0].parent.getX();
                        // console.log('shamt ', shamt);
                        this.ShiftSubMatrix(matrix, childrenGroup[0].parent.getX(), level - 1, shamt);
                    }

                    // If not the last node in level, reset group and add it to it
                    if (i < (matrix[level].length - 1)){
                        childrenGroup = [];
                        firstChildOfGroup = i;
                        childrenGroup.push(child);
                    }
                }
            });
        }
    }

    /**
     * Fits the nodes above the critical level in place
     * @param {The index of the critical level s.t. the tree matrix row index} CLI 
     * @param {The tree matrix} matrix 
     */
    fitCLParents(CLI, matrix){
        // Local variables
        var childrenGroup = [];
        var avgChildLoc = 0;
        var shamt = 0;

        // The code
        for (let level = CLI - 1; level >= 0; level--){

            // if children level exists, go through it and group children by parent 
            if (level + 1 < matrix.length){
                matrix[level + 1].map((child, i) => {
                    if (childrenGroup.length == 0 || child.getParent() == childrenGroup[0].getParent()){
                        // Add the child to the group
                        childrenGroup.push(child);
                    }

                    // If node belonge to a different group or is the last node in level
                    if (child.getParent() != childrenGroup[0].getParent() || i == (matrix[level+1].length - 1)) {
                        // *** Process the group ***
                        // calculate the average location of children group
                        avgChildLoc = this.findAvgLocation(childrenGroup);

                        // calculate shift amount and shift all nodes in the subMatrix that has the
                        // parent node at its bottom right corner to the right.
                        // The column is calculated using the nodes X-values
                        shamt = avgChildLoc - childrenGroup[0].getParent().getX();
                        this.ShiftSubMatrix(matrix, childrenGroup[0].getParent().getX(), level, shamt);

                        // If the node is not the last one in the
                        // level, reset group and add it to the group
                        if ( i < (matrix[level+1].length - 1)){
                            childrenGroup = [];
                            childrenGroup.push(child);
                        }
                    }
                });
            }
        }
    }

    /**
     * Shifts the X-values of the nodes in a particular
     * row to the right by shamt amount of pixels
     * @param {The tree matrix} matrix 
     * @param {The colom (the col index) from which the shift will start} startingCol 
     * @param {The row at which the shift will happen} row 
     * @param {The shift amount in pixels} shamt 
     */
    shiftSubRow(matrix, startingCol, row, shamt){
        matrix[row].map((child, i) => {
            if (i >= startingCol){
                child.setX(child.getX() + shamt);
            }
        });
    }

    /**
     * Shifts all the nodes in the sub-matrix that has its
     * left bottom corner at the node with startingX X-value
     * and startingRow row to the right by shamt shift amount
     * in pixels
     * @param {The tree matrix} matrix 
     * @param {The X-value of the node from which the shift will start} startingX 
     * @param {The row from which the shift will start going up} startingRow 
     * @param {The shift amount in pixels} shamt 
     */
    ShiftSubMatrix(matrix, startingX, startingRow, shamt){
        for (let i = startingRow; i >= 0; i--){
            for (let j = 0; j < matrix[i].length; j++){
                // console.log('i, j', i, j);
                if (matrix[i][j].getX() >= startingX)
                    matrix[i][j].setX(matrix[i][j].getX() + shamt);
            }
        }
    }

    /**
     * Finds the average X-value of all of the nodes
     * @param {An array of nodes} nodesArr 
     */
    findAvgLocation(nodesArr){
        var locationSum = 0;
        nodesArr.map(child => {
            locationSum += child.getX();
        });

        return locationSum/nodesArr.length;
    }


    /**
     * Udates the tree nodes locations according to 
     * the new size of the canvas
     */
    resize(width){
        if (isNaN(width))
            return;

        var factor = (width/2)/this.root.getX();
        // console.log('target loc ', width/2);
        // console.log('the root', this.root);
        // console.log('X = ', this.root.getX());
        // console.log('the factor', factor);
        for (let i = 0; i < this.treeMatrix.length; i++){
            for (let j = 0; j < this.treeMatrix[i].length; j++){
                this.treeMatrix[i][j].setX(this.treeMatrix[i][j].getX() * factor);
            }
        }

        // Resolve collision
        for (let i = 0; i < this.treeMatrix.length; i++){
            for (let j = 1; j < this.treeMatrix[i].length; j++){
                let rightBound = this.treeMatrix[i][j-1].getRightBound();
                let leftBound  = this.treeMatrix[i][j].getLeftBound();
                if (rightBound >= leftBound){
                    // Move the second one to the right
                    this.ShiftSubMatrix(this.treeMatrix, this.treeMatrix[i][j].getX(), this.treeMatrix.length - 1, (rightBound - leftBound) + 2);
                }
            }
        }
    }
}

export default GenericTree;