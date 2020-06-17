import React from 'react'
import p5 from 'p5'
import GenericTree from '../models/GenericTree'
import '../Styles/canvas.css'
import { withSnackbar } from 'notistack';

class DetachedCanvas extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            key : 1,
            tree : null,
            beingEnimated : false,
        }

        this.node = document.createElement('div');
        this.myP5 = null;
    }

    
    Sketch = (p) => {
        p.width = window.innerWidth;
        p.height = window.innerHeight;
        p.tree = null;
        var cnv;

        p.setup = () => {
            p.width = p.width < 200 ? 200 : p.width;
            cnv = p.createCanvas(p.width, p.height);
            cnv.style('visibility: visible');
        }
   
        p.draw = () => {
            p.background('#34495e');
            if (p.tree){
                p.scale(p.tree.getScale());
                p.tree.draw(p);
            } else {
                p.fill('FFFFF');
                p.textAlign(p.CENTER);
                p.textSize(20);
                p.text("NO TREE IS LOADED", p.width/2, p.height/2);
                p.textSize(12);
            }
        }

        p.scaleValue = 1;

        p.windowResized = (width, height) => {
            if (typeof height != 'undefined'){
                p.resizeCanvas(width, height);
                p.redraw();
            }
        }
    }

    componentDidMount(){
        window.addEventListener('message', this.recieveMessage, false);
        window.document.getElementById(this.state.key).appendChild(this.node);
        window.addEventListener("resize", this.resize);
        this.myP5 = new p5(this.Sketch, this.node);
        this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);
    }

    recieveMessage = (e) => {
        if (e.data != ''){
            this.state.tree = new GenericTree();
            this.state.tree.construct(e.data.tree.treeString);
            this.state.tree.setTreeType(e.data.tree.treeType);
            this.state.tree.setId(e.data.tree.id);
            this.state.tree.setScale(e.data.tree.scale);
            this.state.tree.setSteps(e.data.tree.steps);

            this.myP5.tree = this.state.tree;

            this.state.tree.setCenterX((window.innerWidth - 5) / 2);
            this.state.tree.setCenterY(40);
            this.state.tree.center();

            this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);

            this.setState((prevState)=>{
                return {key : e.data}
            });
        }
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
        if (this.state.tree){
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
    }

    resize = () => {
        this.myP5.windowResized(window.innerWidth - 5, window.innerHeight - 5);
        this.setState((prevState) => {
            return {'key' : !prevState.key};
        });
        if (this.state.tree){
            this.state.tree.center();
        }
    }

    handleZoom = (e, value) => {
        if (this.state.tree){
            if (e.ctrlKey){
                this.state.tree.setCenterX(this.state.tree.getCenterX() - (e.clientX - this.state.tree.getCenterX()) * e.deltaY * - 0.05 * (1/this.state.tree.scale));
                this.state.tree.setCenterY(this.state.tree.getCenterY() - (e.clientY - (window.innerHeight - 20) / 2) * e.deltaY * - 0.05 * (1/this.state.tree.scale));
                this.state.tree.setScale(this.state.tree.getScale() - e.deltaY * 0.05);
                this.state.tree.center();
            }
        }

        e.preventDefault();
    }

    treeToCenter = (e) => {
        if (this.state.tree){
            this.state.tree.setCenterX((window.innerWidth - 5) / 2);
            this.state.tree.setCenterY(40);
            this.state.tree.setScale(1);
            this.state.tree.center();
            e.preventDefault();
        }
    }
    
    playSteps = (e) => {
        if (this.state.tree){
            var i = 0;
            var immediatly = 1;
            this.setState({'beingEnimated' : true});
            this.state.tree.beingEnimated = true;
            var steps = this.state.tree.getSteps();
            var delay = 1500;

            (function loop() {
                if (!this.state.tree.beingEnimated){
                    i = steps.length; // skip ahead to the last step
                    immediatly = 0; // To stop immedietly without delay
                }

                // If steps were not empty
                if (i < steps.length){
                    if (steps[i].text != ''){}
                        this.props.enqueueSnackbar(steps[i].text);

                    if (steps[i].treeStr != ''){
                        this.state.tree.construct(steps[i].treeStr);
                        this.state.tree.setNote(steps[i].note);
                    }

                    // center needs to be called twice
                    this.state.tree.center();
                    this.state.tree.center();
                }

                if (i == steps.length - 1)
                    this.stopSteps();

                if (++i < steps.length) {
                    setTimeout(loop.bind(this), delay * immediatly);  // call myself in 1 seconds time if required
                }
            }.bind(this))(); // above function expression is called immediately to start it off
        }
        e.preventDefault();
    }

    stopSteps = (e) => {
        if (this.state.tree){
            this.setState({'beingEnimated' : false});
            this.state.tree.beingEnimated = false;

            if (e){
                var steps = this.state.tree.getSteps();
                this.state.tree.construct(steps[steps.length - 1].treeStr);
                this.state.tree.setNote('');

                // center needs to be called twice
                this.state.tree.center();
                this.state.tree.center();
                e.preventDefault();
            }
        }
    }

    render(){
        return (
            <div>
                <div className='float-right' style={{height : 25, 'position': 'absolute', 'top': '5px', 'right': '5px'}}> 
                    <a key={this.state.beingEnimated} href='#' className='badge badge-light'  
                        onClick={this.state.tree && !this.state.tree.beingEnimated?this.playSteps:this.stopSteps}
                        style={{'margin-right':'0.5em'}}>
                        <div className={this.state.tree && !this.state.tree.beingEnimated?'play':'stop'} style={{'color' : '#FFFFFF'}}></div>
                    </a>
                    <a href='#' className='badge badge-light'  onClick={this.treeToCenter}
                        style={{'margin-right':'0.5em'}}>
                        <div className='center' style={{'color' : '#FFFFFF'}} ></div>
                    </a>
                </div>
                <div>
                    <div style={{'background-color' : '#34495e' , 'height' : window.innerHeight}} 
                    id={this.state.key}
                    onTouchStart={this.pressed} onMouseDown={this.pressed} 
                    onTouchMove={this.dragged} onMouseMove={this.dragged} 
                    onTouchEnd={this.released} onMouseUp={this.released}
                    onWheel={this.handleZoom} 
                    />
                </div>
            </div>
        );
    }
}

export default withSnackbar(DetachedCanvas);