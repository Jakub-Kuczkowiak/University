package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.ServiceDaoImpl;
import com.januszsoft.bikerental.backend.models.Service;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/service")
@Produces(MediaType.APPLICATION_JSON)
public class ServiceService {

  @Autowired
  ServiceDaoImpl services;

  @GET
  @Path("/")
  public Response getServiceInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(services.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getServiceInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Service aService = services.get(id);
    if(aService == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aService).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addService(@PathParam("id") Integer id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteService(@PathParam("id") Integer id) {
    services.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeServicenBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
