#!/bin/bash
git checkout heroku_master
git merge master
git push heroku heroku_master:master
git checkout master
