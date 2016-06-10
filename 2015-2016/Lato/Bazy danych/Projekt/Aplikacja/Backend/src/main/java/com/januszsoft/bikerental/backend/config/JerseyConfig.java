package com.januszsoft.bikerental.backend.config;

import com.januszsoft.bikerental.backend.services.*;
import org.glassfish.jersey.server.ResourceConfig;
import org.springframework.stereotype.Component;

import javax.ws.rs.ApplicationPath;

@Component
@ApplicationPath("/")
public class JerseyConfig extends ResourceConfig {
  public JerseyConfig() {
    register(MvcConfiguration.class);
    register(BikeService.class);
    register(IssueService.class);
    register(PaymentService.class);
    register(RentService.class);
    register(ServicemanService.class);
    register(ServiceService.class);
    register(StationService.class);
    register(StationService.class);
    register(UsserService.class);
    register(LoginService.class);
    register(LogoutService.class);

  }
}
