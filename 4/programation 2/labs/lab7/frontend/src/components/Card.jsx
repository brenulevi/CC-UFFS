import React from "react";

import { Button } from "@mui/material";

import "./Card.css";

function Card({ courseName, onSelectCourse, courses }) {
    function setCourse() {
        let id;
        courses.forEach((course) => {
            if(course.name === courseName)
                id = parseInt(course.id);
        })

        onSelectCourse(id);
    }

    return (
        <div className="col" onClick={setCourse}>
            <Button variant="contained" style={{
                fontWeight: "bold",
                borderRadius: "2px",
                backgroundColor: "#00693E"
            }}>{courseName}</Button>
        </div>
    );
}

export default Card;