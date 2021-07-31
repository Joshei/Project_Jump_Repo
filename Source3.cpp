window.clear(gColor);
window.draw(marioSpriteL);
character.EnemyObject->changePlatformEdgesForEnemy(window, -5);
miscObject.moveEnemies(window, 2, 2, 0);
platform::SearchVectorForPlatforms(vectorPlatforms, window, -5, 0, 0);
character.EnemyObject->moveEnemies(window, 2, 0, 0);
window.display();




miscObject.moveEnemies(window, 10, 0, 1);
character.EnemyObject->changePlatformEdgesForEnemy(window, -5);
platform::drawAllPlatforms(vectorPlatforms, window);
character.EnemyObject->moveEnemies(window, 10, -10, 0);



miscObject.moveEnemies(window, 10, 0, 1);
platform::SearchVectorForPlatforms(vectorPlatforms, window, 0, 0.0f, 0);
character.EnemyObject->moveEnemies(window, 10, -1, 0);



move enemies
draw platforms (as needed)
move enemies
