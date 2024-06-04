import * as THREE from "three";
import { OrbitControls } from "three/addons/controls/OrbitControls.js";
import { GLTFLoader } from "three/addons/loaders/GLTFLoader.js";
import { MTLLoader } from "three/addons/loaders/MTLLoader.js";

const scene = new THREE.Scene();
const timer = new THREE.Clock();
const camera = new THREE.PerspectiveCamera(
  75,
  window.innerWidth / window.innerHeight,
  0.1,
  1000
);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const controls = new OrbitControls(camera, renderer.domElement);
controls.enablePan = false;
controls.minZoom = 50;
const objLoader = new GLTFLoader();

let plane;
let tower;

objLoader.load("./assets/airplane/scene.gltf", (gltf) => {
  scene.add(gltf.scene);
  gltf.scene.position.z = 20;
  gltf.scene.position.y = 60;
  gltf.scene.rotation.y = THREE.MathUtils.degToRad(180);
  plane = gltf.scene;
});

objLoader.load("./assets/tower/scene.gltf", (gltf) => {
  scene.add(gltf.scene);
  gltf.scene.position.y = -15;
  tower = gltf.scene;
});

const cubeLoader = new THREE.CubeTextureLoader();
cubeLoader.setPath("./assets/skybox/");
const textureCube = cubeLoader.load([
  "right.jpg",
  "left.jpg",
  "top.jpg",
  "bottom.jpg",
  "front.jpg",
  "back.jpg",
]);
scene.background = textureCube;

const inviObj = new THREE.Object3D();

scene.add(inviObj);

const ambientLight = new THREE.AmbientLight(undefined, 0.2);
const directionalLight = new THREE.DirectionalLight();

scene.add(ambientLight);
scene.add(directionalLight);

camera.position.z = 5;
controls.update();

function animate() {
  requestAnimationFrame(animate);

  directionalLight.target = inviObj;
  inviObj.position.set(0, 0, 0);

  if (plane && tower) {
      plane.position.x = Math.sin(timer.getElapsedTime()) * 20;
      plane.position.z = Math.cos(timer.getElapsedTime()) * 20;
      plane.lookAt(tower.position);
      plane.rotation.y += THREE.MathUtils.degToRad(90);
      controls.target = plane.position;
  }

  controls.update()

  renderer.render(scene, camera);
}

animate();
