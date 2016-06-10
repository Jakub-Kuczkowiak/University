'use strict';

require('angular');
require('angular-cookies');
require('angular-resource');

window._ = require('lodash');
require('angular-simple-logger');
require('angular-google-maps');

var MainController = require('./controllers/MainController.js'),
    AuthenticationController = require('./controllers/AuthenticationController.js'),
    StationController = require('./controllers/StationController.js'),

    AuthenticationService = require('./services/AuthenticationService.js'),
    StationService = require('./services/StationService.js'),
    UserService = require('./services/UserService.js'),
    ServiceService = require('./services/ServiceService.js'),
    BikeService = require('./services/BikeService.js'),

    InfoPanelDirective = require('./directives/InfoPanelDirective.js'),
    UserPanelDirective = require('./directives/UserPanelDirective.js'),
    RegistrationPanelDirective = require('./directives/RegistrationPanelDirective.js');

angular
    .module('bikerental', [
        'ngCookies',
        'ngResource',
        'uiGmapgoogle-maps'
    ])
    .factory('Authentication', AuthenticationService)
    .factory('Station', StationService)
    .factory('User', UserService)
    .factory('Service', ServiceService)
    .factory('Bike', BikeService)

    .controller('MainController', MainController)
    .controller('AuthenticationController', AuthenticationController)
    .controller('StationController', StationController)

    .directive('stationInfoPanel', InfoPanelDirective)
    .directive('userPanel', UserPanelDirective)
    .directive('registrationPanel', RegistrationPanelDirective);

