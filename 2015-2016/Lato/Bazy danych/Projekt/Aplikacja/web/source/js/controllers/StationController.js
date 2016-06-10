'use strict';

// @ngInject
module.exports = function($http, $timeout, $scope, Station, Authentication) {
    var vm = this;

    vm.currentTab = 0;
    vm.stations = Station.query();

    vm.isTabSet = isTabSet;
    vm.setTab = setTab;
    vm.rentBike = rentBike;
    vm.unrentBike = unrentBike;

    function isTabSet(_id) {
        return vm.currentTab == _id;
    }

    function setTab(_id) {
        vm.currentTab = _id;
    }

    function rentBike() {
        console.log('rentBike()');
        var bikeId = $("input[name=bikeOption]:checked").val();
        var userId = $scope.userInfo.id;

        $timeout(function(){
            $http.post('/api/rent/?bike=' + bikeId + "&usser=" + userId).then(
                rentSuccessFn,
                rentErrorFn
            );

            function rentSuccessFn() {
                window.location.reload();
            }

            function rentErrorFn() {
                console.log('Error while renting bike');
            }
        }, 500);

    }

    function unrentBike(station) {
        $timeout(function() {
            $http({
                method: 'DELETE',
                url: '/api/rent/?bike=' + $scope.userInfo.currentBike.id + "&station=" + station.id
            }).then(unrentSuccessFn, unrentErrorFn);

            function unrentSuccessFn() {
                window.location.reload();
            }

            function unrentErrorFn() {
                console.log('Error while unrenting bike');
            }
        }, 500);
    }

};
