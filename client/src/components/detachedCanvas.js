import React from 'react'
import Canvas from './canvas'
import p5 from 'p5'
import GenericTree from '../models/GenericTree'

class DetachedCanvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            msg : 1,
            tree : new GenericTree()
        }
        this.recieveMessage = this.recieveMessage.bind(this);
        this.node = document.createElement('div');
        this.myP5 = new p5(this.Sketch, this.node);
        this.handleZoom = this.handleZoom.bind(this);
    }

    
    Sketch = (p) => {
        p.width = window.innerWidth;
        p.height = window.innerHeight;
        p.tree = null;

        var cnv;

        p.setup = () => {
            cnv = p.createCanvas(p.width, p.height - 40);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree){
                p.scale(p.tree.getScale());
                p.tree.draw(p, p.width);
            }
        }

        p.scaleValue = 1;

        p.windowResized = (width, height) => {
            if (p.tree)
                p.tree.resize(width, true);
            p.resizeCanvas(width, height);
            p.redraw();
        }
    }

    componentDidMount(){
        window.addEventListener('message', this.recieveMessage, false);
        window.document.getElementById(this.state.msg).appendChild(this.node);
    }

    recieveMessage(e){
        this.setState((prevState)=>{
            // Using the recieved message to build the tree
            prevState.tree.construct(e.data.tree.treeString);
            prevState.tree.setTreeType(e.data.tree.treeType);
            prevState.tree.setId(e.data.tree.id);
            prevState.tree.setScale(e.data.tree.scale);

            // Updatng the p5 object
            this.myP5.tree = prevState.tree;

            // deciding on height and width
            var treeWidth = this.state.tree.getWidth() + 0.2 * this.state.tree.getWidth();
            var treeHeight = this.state.tree.getHeight();
            treeWidth = /*treeWidth > window.innerWidth - 5 ? treeWidth :*/ window.innerWidth - 5;
            treeHeight = /*treeHeight > window.innerHeight - 5 ? treeHeight :*/ window.innerHeight - 5;

            // resizing
            this.myP5.tree.putInView(treeWidth/2);
            this.myP5.windowResized(treeWidth, treeHeight);

            return {msg : e.data}
        });
    }

    pressed = (e) => {
        this.mousePressed = true;
        if (e.touches){
            this.initialX = e.touches[0].clientX;
            this.initialY = e.touches[0].clientY;
        } else {
            this.initialX = e.clientX;
            this.initialY = e.clientY;
        }

        e.preventDefault();
    }

    released = (e) => {
        this.mousePressed = false;
        
        e.preventDefault();
    }

    dragged = (e) => {
        e.preventDefault();

        if (this.mousePressed){
            // update initial values
            if (e.touches){
                this.state.tree.moveTree(e.changedTouches[0].clientX - this.initialX, 
                                         e.changedTouches[0].clientY - this.initialY);
                this.initialX = e.touches[0].clientX;
                this.initialY = e.touches[0].clientY;
            } else {
                this.state.tree.moveTree(e.clientX - this.initialX, e.clientY - this.initialY);
                this.initialX = e.clientX;
                this.initialY = e.clientY;
            }

        }
    }

    handleZoom(e, value){
        var rect = e.target.getBoundingClientRect();
        if (e.ctrlKey){
            e.preventDefault();
            this.state.tree.setScale(this.state.tree.getScale() - e.deltaY * 0.05);

            // deciding on height and width
            var treeWidth = this.state.tree.getWidth() + 0.2 * this.state.tree.getWidth();
            var treeHeight = this.state.tree.getHeight();
            treeWidth = /*treeWidth > window.innerWidth - 5 ? treeWidth :*/ window.innerWidth - 5;
            treeHeight = /*treeHeight > window.innerHeight - 5 ? treeHeight :*/ window.innerHeight - 5;

            // resizing
            this.myP5.windowResized(treeWidth, treeHeight);
        }
    }

    render(){
        return (
            <div style={{'background-color' : '#34495e' , 'height' : window.innerHeight}} 
                 id={this.state.msg}
                 onTouchStart={this.pressed} onMouseDown={this.pressed} 
                 onTouchMove={this.dragged} onMouseMove={this.dragged} 
                 onTouchEnd={this.released} onMouseUp={this.released}
                 onWheel={this.handleZoom} 
            />
        );
    }
}

export default DetachedCanvas;