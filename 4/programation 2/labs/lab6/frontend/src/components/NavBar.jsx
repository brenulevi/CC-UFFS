import React, { useEffect, useState } from "react";
import axios from "axios";

import logo from "../images/uffs assinatura visual preferencial _fundo verde _RGB.png";
import { Button } from "@mui/material";

import "./NavBar.css";

axios.defaults.baseURL = "http://localhost:3333/";
axios.defaults.headers.common["Content-Type"] = "application/json;charset=utf-8";


function NavBar() {
    const [follow, setFollow] = useState("Follow");

    function handleFollow() {
        const res = axios.put("/follow");
        res.then((query) => {
            setFollow(query.data.data);
        })
    }

    useEffect(() => {
        const res = axios.get("/follow");
        res.then((query) => {
            setFollow(query.data);
        })
    }, []);

    return (
        <header>
            <nav id="navbar" className="navbar navbar-expand-lg navbar-dark">
                <a href="#navbar" className="navbar-brand">
                    <img src={logo} className="logo" alt="uffs logo" />
                </a>

                <div className="collapse navbar-collapse">
                    <Button variant="contained" onClick={() => handleFollow()}>{follow}</Button>

                    <ul className="navbar-nav mr-auto">
                        <li className="nav-item">
                            <a href=".nav-item" className="nav-link">CCRs</a>
                        </li>
                        <li className="nav-item">
                            <a href=".nav-item" className="nav-link">Cursos</a>
                        </li>
                    </ul>
                </div>
            </nav>
        </header>
    );
}

export default NavBar;