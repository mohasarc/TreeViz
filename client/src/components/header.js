import React from 'react'

class Header extends React.Component{
    constructor(props){
        super(props);
        this.welcomeMsg = props.welcomeMsg;
        this.h = props.h;
    }
    render(){
        if (this.h == 'h1')
            return <h1>{this.welcomeMsg}</h1>;
        else if (this.h == 'h2')
            return <h2>{this.welcomeMsg}</h2>;
        else
            return <p>{this.welcomeMsg}</p>
    }
}

export default Header;