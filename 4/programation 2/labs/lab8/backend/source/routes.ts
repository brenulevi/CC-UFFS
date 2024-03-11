import { Router } from "express";

import { getCourse } from "./controllers";

const router : Router = Router();

router.get("/", getCourse);

export default router;