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
@Path("/login")
@Produces(MediaType.APPLICATION_JSON)
public class LoginService {

  @Autowired
  SessionDaoImpl sessions;

  @Autowired
  UsserDaoImpl ussers;

  @GET
  @Path("/")
  public Response getBikeInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(sessions.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{cookieHash}")
  public Response getSessionInfo(@PathParam("cookieHash") String cookiehash) {
    Session aSession = sessions.getByHash(cookiehash);
    if(aSession == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aSession).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/")
  public Response login(@QueryParam("userLogin") String userLogin, @QueryParam("passwordHash") String passwordHash) {
    String token = UUID.randomUUID().toString();
    passwordHash = UsserService.getHashedPassword(passwordHash);

    Usser usser = ussers.getUserByPesel(userLogin);

    if(usser == null) {
      return Response.status(Response.Status.NOT_FOUND).type(MediaType.APPLICATION_JSON).build();
    }

    if(!usser.getPasswordhash().equals(passwordHash)) {
      return Response.status(Response.Status.UNAUTHORIZED).type(MediaType.APPLICATION_JSON).build();
    }

    Session session = new Session();
    session.setHash(token);
    session.setLogin(userLogin);

    NewCookie responseCookie = new NewCookie("bike-rental-login-cookie",
      token, "/", "", "bike-rental-login-cookie", 60 * 60 * 24, false);

    sessions.saveOrUpdate(session);
    return Response.ok(sessions.getByHash(token)).type(MediaType.APPLICATION_JSON).cookie(responseCookie).build();
  }
}
