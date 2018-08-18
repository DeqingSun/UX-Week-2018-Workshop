//snap version on https://snap.berkeley.edu/snapsource/snap.html#present:Username=deqing&ProjectName=testMicrobit

var microBitImg;

var rotationAngle = 0;

function setup() {
  createCanvas(windowWidth, windowHeight);
  img = loadImage("microbit-front.png"); // Load the image
}

function draw() {

  background(255);

  ratioX = windowWidth / img.width;
  ratioY = windowHeight / img.height;
  ratio = min(ratioX, ratioY);

  resizeWidth = img.width * ratio * .75;
  resizeHeight = img.height * ratio * .75;

  resetMatrix();
  translate(windowWidth / 2, windowHeight / 2);
  rotate(rotationAngle);

  image(img, -resizeWidth / 2, -resizeHeight / 2, resizeWidth, resizeHeight);

  noFill();
  stroke(255, 0, 0);
  strokeWeight(5 * ratio);

  if (keyIsDown(48)) {
    ellipse((-181 / 431.0 * resizeWidth), (123 / 364.0 * resizeHeight), 50 * ratio, 50 * ratio);
  }
  if (keyIsDown(49)) {
    ellipse((-96 / 431.0 * resizeWidth), (123 / 364.0 * resizeHeight), 50 * ratio, 50 * ratio);
  }
  if (keyIsDown(50)) {
    ellipse((-1 / 431.0 * resizeWidth), (123 / 364.0 * resizeHeight), 50 * ratio, 50 * ratio);
  }
  if (keyIsDown(65)) {
    ellipse((-168 / 431.0 * resizeWidth), (5 / 364.0 * resizeHeight), 50 * ratio, 50 * ratio);
  }
  if (keyIsDown(66)) {
    ellipse((167 / 431.0 * resizeWidth), (5 / 364.0 * resizeHeight), 50 * ratio, 50 * ratio);
  }

  resetMatrix();
}

function keyPressed() {
  //http://keycode.info/
  if (keyCode == 48) { //0 key
    print("0 pressed");
  } else if (keyCode == 49) { //1 key
    print("1 pressed");
  } else if (keyCode == 50) { //2 key
    print("2 pressed");
  } else if (keyCode == 65) { //A key
    print("a pressed");
  } else if (keyCode == 66) { //B key
    print("b pressed");
  } else if (keyCode == 81) { //Q key
    rotationAngle = QUARTER_PI * 0;
  } else if (keyCode == 87) { //W key
    rotationAngle = QUARTER_PI * 1;
  } else if (keyCode == 69) { //E key
    rotationAngle = QUARTER_PI * 2;
  } else if (keyCode == 82) { //R key
    rotationAngle = QUARTER_PI * 3;
  } else if (keyCode == 84) { //T key
    rotationAngle = QUARTER_PI * 4;
  } else if (keyCode == 89) { //Y key
    rotationAngle = QUARTER_PI * 5;
  } else if (keyCode == 85) { //T key
    rotationAngle = QUARTER_PI * 6;
  } else if (keyCode == 73) { //Y key
    rotationAngle = QUARTER_PI * 7;
  }

}

function keyReleased() {
  if (keyCode == 48) { //0 key
    print("0 released");
  } else if (keyCode == 49) { //1 key
    print("1 released");
  } else if (keyCode == 50) { //2 key
    print("2 released");
  } else if (keyCode == 65) { //A key
    print("a released");
  } else if (keyCode == 66) { //B key
    print("b released");
  }
}

function windowResized() {
  resizeCanvas(windowWidth, windowHeight);
}