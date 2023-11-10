import express, { Express, Router } from "express";
import bodyParser from "body-parser";
import cors from "cors";

import routes from "./routes";

const app : Express = express();

app.use(cors());
app.use(bodyParser.json());
app.use(routes);

app.listen(3333, () => console.log("Running on port 3333..."));