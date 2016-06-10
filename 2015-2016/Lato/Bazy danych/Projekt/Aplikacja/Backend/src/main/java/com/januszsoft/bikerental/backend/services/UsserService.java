package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.januszsoft.bikerental.backend.dao.UsserDaoImpl;
import com.januszsoft.bikerental.backend.models.Usser;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.io.IOException;
import java.security.MessageDigest;

@Component
@Path("/usser")
@Produces(MediaType.APPLICATION_JSON)
public class UsserService {

  @Autowired
  UsserDaoImpl ussers;

  @GET
  @Path("/")
  public Response getUsserInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(ussers.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{pesel}")
  public Response getUsserInfo(@PathParam("pesel") String pesel) throws JsonProcessingException, JSONException {
    Usser aUser = ussers.getUserByPesel(pesel);

    if(aUser == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aUser).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addUsser(String queryBody) throws IOException {
    ObjectMapper mapper = new ObjectMapper();
    Usser usser = mapper.readValue(queryBody, Usser.class);
    usser.setPasswordhash( getHashedPassword(usser.getPasswordhash()) );
    ussers.saveOrUpdate(usser);
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteUser(@PathParam("id") Integer id) {
    ussers.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeUserBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

  public static String getHashedPassword(String passwordToHash) {
    String generatedPassword = null;
    try {
      MessageDigest md = MessageDigest.getInstance("MD5");
      md.update(passwordToHash.getBytes());
      byte[] bytes = md.digest();
      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < bytes.length; i++) {
        sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
      }
      //Get complete hashed password in hex format
      generatedPassword = sb.toString();
    } catch (Exception e) {
    }

    return generatedPassword;
  }

  }
