const fs = require("fs");
const path = require("path");

const { Router } = require("express");
const router = Router();

const db = require("./db.json");

router.get("/course", (req, res) => {
    res.json(db.course);
});

router.get("/schedule/:id", (req, res) => {
    const { id } = req.params;
    db.schedules.forEach(course => {
        if (parseInt(course.courseId) === parseInt(id))
            res.json(course);
    })
});

router.get("/follow", (req, res) => {
    res.json(db.follow);
})

router.put("/follow", (req, res) => {
    if (db.follow === "Follow") {
        db.follow = "Following";
        console.log("Recebi um follow");
    } else if (db.follow === "Following") {
        db.follow = "Follow";
        console.log("Recebi unfollow");
    }

    fs.writeFile(path.join(__dirname, "db.json"), JSON.stringify(db, null, 2), err => {
        if(err)
            res.status(400).json({ error: err});
        res.status(200).json({ status: "Updated", data: db.follow });
    });

});

module.exports = router;