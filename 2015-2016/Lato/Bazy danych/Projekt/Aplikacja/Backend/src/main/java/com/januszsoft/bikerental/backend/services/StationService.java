package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.StationDaoImpl;
import com.januszsoft.bikerental.backend.models.Station;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Component
@Path("/station")
@Produces(MediaType.APPLICATION_JSON)
public class StationService {

  @Autowired
  StationDaoImpl stations;

  @GET
  @Path("/")
  public Response getStationInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(stations.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getStationInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Station aStation = stations.get(id);
    if(aStation == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aStation).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}/bikes")
  public Response getAllBikes(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Station aStation = stations.get(id);
    if(aStation == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(stations.getListOfBikes(id)).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addStation(@PathParam("id") Integer id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

  @DELETE
  @Path("/{id}")
  public Response deleteStation(@PathParam("id") Integer id) {
    stations.delete(id);
    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeStationBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
