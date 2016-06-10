'use strict';

// @ngInject
module.exports = function ($scope, Station, Service) {
    var vm = this;

    vm.stations = [];
    vm.services = [];
    vm.shouldShowInfoPanel = false;
    vm.currentStationInfo = [];
    vm.currentTab = 0;

    vm.initialMapCenter = {
        latitude: 51.111651,
        longitude: 17.058095
    };
    vm.myPosition = {
        latitude: 51.111651,
        longitude: 17.058095
    };

    vm.map = {
        center: this.initialMapCenter,
        zoom: 12,
        options: {
            disableDefaultUI: false,
            disableDoubleClickZoom: false,
            draggable: true,
            scrollwheel: true,
            panControl: true,
            enableHighAccuracy: true,
            styles: [{"featureType":"all","elementType":"labels.text.fill","stylers":[{"saturation":36},{"color":"#000000"},{"lightness":40}]},{"featureType":"all","elementType":"labels.text.stroke","stylers":[{"visibility":"on"},{"color":"#000000"},{"lightness":16}]},{"featureType":"all","elementType":"labels.icon","stylers":[{"visibility":"off"}]},{"featureType":"administrative","elementType":"geometry.fill","stylers":[{"color":"#000000"},{"lightness":20}]},{"featureType":"administrative","elementType":"geometry.stroke","stylers":[{"color":"#000000"},{"lightness":17},{"weight":1.2}]},{"featureType":"landscape","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":20}]},{"featureType":"poi","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":21}]},{"featureType":"road.highway","elementType":"geometry.fill","stylers":[{"color":"#000000"},{"lightness":17}]},{"featureType":"road.highway","elementType":"geometry.stroke","stylers":[{"color":"#000000"},{"lightness":29},{"weight":0.2}]},{"featureType":"road.arterial","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":18}]},{"featureType":"road.local","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":16}]},{"featureType":"transit","elementType":"geometry","stylers":[{"color":"#000000"},{"lightness":19}]},{"featureType":"water","elementType":"geometry","stylers":[{"color":"#0f252e"},{"lightness":17}]}]
        },
        events: {
            click : function (mapModel, eventName, originalEventArgs) {
                vm.hideInfoPanel();
                vm.setTab(0);
            }
        },
        control: {}
    };

    vm.setTab = setTab;
    vm.isTabSet = isTabSet;
    vm.showInfoPanel = showInfoPanel;
    vm.hideInfoPanel = hideInfoPanel;
    vm.showDriveInfo = showDriveInfo;

    init();

    function init() {
        vm.stations = Station.query();
        vm.services = Service.query();

        vm.stations.$promise.then(function(response) {
            var i;
            for(i = 0; i < vm.stations.length; i++) {
                vm.stations[i].location = [];
                vm.stations[i].location.push(vm.stations[i].latitude);
                vm.stations[i].location.push(vm.stations[i].longitude);
            }
        });

        vm.services.$promise.then(function(response) {
            var i;
            for(i = 0; i < vm.services.length; i++) {
                vm.services[i].location = [];
                vm.services[i].location.push(vm.services[i].latitude);
                vm.services[i].location.push(vm.services[i].longitude);
            }
        });

        if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(function (position) {
                vm.myPosition.latitude = position.coords.latitude;
                vm.myPosition.longitude = position.coords.longitude;

                $scope.$apply();
            });
        }
    }

    function setTab(tabId) {
        vm.currentTab = tabId;
    }

    function isTabSet(tabId) {
        return vm.currentTab == tabId;
    }

    function showInfoPanel(station) {
        var bikes = Station.query({stationId : station.id, subResource: 'bikes'});

        bikes.$promise.then(function(response) {
            station.bikes = [];
            var i;
            for(i = 0; i < bikes.length; i++) {
                station.bikes.push(bikes[i]);
            }

            vm.shouldShowInfoPanel = true;
            vm.currentStationInfo = station;
        });
    }

    function hideInfoPanel() {
        vm.shouldShowInfoPanel = false;
        vm.currentStationInfo = [];
        $scope.$apply();
    }

    var directionsDisplay = new google.maps.DirectionsRenderer({suppressMarkers: true});

    function showDriveInfo(latitude, longitude) {
        this.setTab(1);
        var startPosition = new google.maps.LatLng(vm.myPosition.latitude, vm.myPosition.longitude);
        var endPosition = new google.maps.LatLng(longitude, latitude);

        var request = {
            origin : startPosition,
            destination : endPosition,
            travelMode : google.maps.TravelMode.WALKING
        };

        var mapInstance = this.map.control.getGMap();
        var detailedInfo = document.getElementById("drive-info");
        directionsDisplay.setMap(mapInstance);
        directionsDisplay.setPanel(detailedInfo);


        var directionsService = new google.maps.DirectionsService();
        directionsService.route(request, function (response, status) {
            if(status == google.maps.DirectionsStatus.OK) {
                directionsDisplay.setDirections(response);
            }
        });
    }
};

