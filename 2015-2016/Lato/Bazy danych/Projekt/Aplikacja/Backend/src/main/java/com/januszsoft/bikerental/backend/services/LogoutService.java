package com.januszsoft.bikerental.backend.services;

import com.januszsoft.bikerental.backend.dao.SessionDaoImpl;
import com.januszsoft.bikerental.backend.dao.UsserDaoImpl;
import com.januszsoft.bikerental.backend.models.Session;
import com.januszsoft.bikerental.backend.models.Usser;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.NewCookie;
import javax.ws.rs.core.Response;
import java.util.UUID;

@Component
@Path("/logout")
@Produces(MediaType.APPLICATION_JSON)
public class LogoutService {

  @Autowired
  SessionDaoImpl sessions;

  @Autowired
  UsserDaoImpl ussers;

  @POST
  @Path("/")
  public Response login(@CookieParam("kebab-explorer-login-cookie") String tokenHash) {

    if (tokenHash == null || tokenHash.isEmpty()) {
      return Response.ok().build();
    }

    sessions.deleteWithHash(tokenHash);

    NewCookie responseCookie = new NewCookie("kebab-explorer-login-cookie",
      "", "/", "", "kebab-explorer-login-cookie", 0, false);

    return Response.ok().type(MediaType.APPLICATION_JSON).cookie(responseCookie).build();
  }
}

