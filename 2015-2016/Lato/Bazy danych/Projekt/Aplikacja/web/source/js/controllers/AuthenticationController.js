'use strict';

// @ngInject
module.exports = function ($location, Authentication, User, Bike, $q, $scope, $timeout) {
    var SUCCESS_URL = '/',
        PROFILE_URL = '/profile/',
        vm = this;

    vm.isAuthenticated = Authentication.isAuthenticated;
    vm.getLogin = Authentication.getAuthenticatedAccountLogin;
    vm.login = login;
    vm.logout = logout;
    vm.gotoProfile = gotoProfile;
    vm.showRegisterPanel = showRegisterPanel;
    vm.register = register;
    vm.recolor = recolor;
    vm.canRentBike = canRentBike;
    vm.canUnrentBike = canUnrentBike;

    activate();

    function showRegisterPanel() {
        $('#registrationPanel').modal('show');
    }

    function register() {
        var newUserData = {
            pesel: vm.pesel,
            passwordhash: vm.password,
            name: vm.name,
            surname: vm.surname,
            address: vm.address,
            email: vm.email,
            phonenumber: vm.phone,
            balance: 0,
            bike: null,
            id: null
        };

        function registerSuccessFn() {
            window.location.reload();
        }

        function registerErrorFn(response) {
            alert('Wprowadzono błędne dane!');
            console.log('REGISTER ERROR', response);
        }


        Authentication.register("", newUserData).then(
            registerSuccessFn,
            registerErrorFn
        );
    }


    function login() {
        function loginSuccessFn() {
            $location.url(SUCCESS_URL);
            window.location.reload();
        }

        function loginErrorFn(response) {
            console.log('LOGIN CONTROLLER ERROR', response);
            document.getElementById("loginInput").style.backgroundColor = "red";
            document.getElementById("passwordInput").style.backgroundColor = "red";
        }

        Authentication.login(vm.email, vm.password).then(
            loginSuccessFn,
            loginErrorFn
        );
    }

    function logout() {
        Authentication.logout();
        $location.url(SUCCESS_URL);
    }

    function activate() {
        $timeout(function () {
            getUserInfo();
        }, 1000);
    }

    function setInfo(_info) {
        $scope.userInfo = {
            id: _info.id,
            pesel: _info.pesel,
            name: _info.name,
            surname: _info.surname,
            address: _info.address,
            email: _info.email,
            phone: _info.phonenumber,
            balance: _info.balance
        };

        if(_info.bike == null) {
            $scope.userInfo.currentBike = "brak";
        }
        else {
            if($scope.userInfo.currentBike == null || $scope.userInfo.currentBike == undefined) {
                var bikeInfo = Bike.get({bikeId: _info.bike});

                bikeInfo.$promise.then(function (response) {
                    $scope.userInfo.currentBike = {};
                    $scope.userInfo.currentBike.id = response.id;
                    $scope.userInfo.currentBike.color = response.color;
                    $scope.userInfo.currentBike.modelname = response.modelname;
                });
            }
        }
    }

    function getUserInfo() {
        if (vm.isAuthenticated()) {
            var currentUserId = Authentication.getAuthenticatedAccountLogin();
            User.get({userLogin: currentUserId}).$promise.then(function (response) {
                return $q(function successInfoGet(resolve) {
                    setInfo(response);
                    resolve(response);
                });
            });
        }
    }

    function gotoProfile() {
        $location.url(PROFILE_URL);
        $('#userPanel').modal('show');
    }

    function recolor() {
        document.getElementById("loginInput").style.backgroundColor = "";
        document.getElementById("passwordInput").style.backgroundColor = "";
    }



    function canRentBike() {
        return vm.isAuthenticated() && ($scope.userInfo.currentBike == "brak");
    }

    function canUnrentBike() {
        return vm.isAuthenticated() && ($scope.userInfo.currentBike != "brak");
    }
};