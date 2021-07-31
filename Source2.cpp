//jump left from right

positionX = positionX + VELOCITYX;


int difference = rightEndzoneLine - currentCharacterPlacement;
leftCrossoverAmount = difference;
rightCrossovereAmount = VELOCITYX - leftCrossoverAmount;

//platform::SearchVectorForPlatforms(vector, window, leftCrossoverAmount, 0.0f, 0);
platform::advanceAllPlatforms(vector, leftCrossoverAmount);
isMoving = "left";
marioSpriteL.setPosition(POSXCENTER, positionY);
marioSpriteR.setPosition(POSXCENTER, positionY);


//jump left from mid

positionX = positionX - VELOCITYX;

//looks right
int difference = leftEndzoneLine - currentCharacterPlacement;
rightCrossovereAmount = VELOCITYX - difference;
leftCrossoverAmount = VELOCITYX - rightCrossovereAmount;
//platform::SearchVectorForPlatforms(vector, window, rightCrossovereAmount, 0.0f, 0);
platform::advanceAllPlatforms(vector, rightCrossovereAmount);
marioSpriteL.setPosition(positionX, positionY);
marioSpriteR.setPosition(positionX, positionY);
isMoving = "left";