import React from 'react';
import Badge from 'react-bootstrap/Badge'

class Canvasno extends React.Component{
    constructor(props){
        super(props);
        this.no = props.no;
        console.log(this.no);
    }

    render(){
        return <Badge variant="light">{this.no}</Badge>
    }
}

export default Canvasno;