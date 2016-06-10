package com.januszsoft.bikerental.backend.services;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.januszsoft.bikerental.backend.dao.BikeDaoImpl;
import com.januszsoft.bikerental.backend.dao.RentDaoImpl;
import com.januszsoft.bikerental.backend.dao.StationDaoImpl;
import com.januszsoft.bikerental.backend.dao.UsserDaoImpl;
import com.januszsoft.bikerental.backend.models.Bike;
import com.januszsoft.bikerental.backend.models.Rent;
import com.januszsoft.bikerental.backend.models.Usser;
import org.json.JSONException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Component;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.sql.Timestamp;

@Component
@Path("/rent")
@Produces(MediaType.APPLICATION_JSON)
public class RentService {

  @Autowired
  RentDaoImpl rents;

  @Autowired
  BikeDaoImpl bikes;

  @Autowired
  UsserDaoImpl ussers;

  @GET
  @Path("/")
  public Response getRentInfo() throws JSONException {
    return Response.status(Response.Status.OK).entity(rents.findall()).type(MediaType.APPLICATION_JSON).build();
  }

  @GET
  @Path("/{id}")
  public Response getRentInfo(@PathParam("id") Integer id) throws JsonProcessingException, JSONException {
    Rent aRent = rents.get(id);
    if(aRent == null) {
      return Response.status(Response.Status.NOT_FOUND).build();
    }
    else return Response.status(Response.Status.OK).entity(aRent).type(MediaType.APPLICATION_JSON).build();
  }

  @POST
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response addRent(@QueryParam("bike") int bikeID, @QueryParam("usser") int usserID) {
    Rent rent = new Rent();
    rent.setBike(bikeID);
    rent.setUsser(usserID);
    java.util.Date date= new java.util.Date();
    rent.setStartdate(new Timestamp(date.getTime()));
    rents.saveOrUpdate(rent);

    Usser usser = ussers.get(usserID);
    usser.setBike(bikeID);
    ussers.saveOrUpdate(usser);

    Bike bike = bikes.get(bikeID);
    bike.setStation(null);
    bikes.saveOrUpdate(bike);

    return Response.ok().build();
  }

  @DELETE
  @Path("/")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response UnRent(@QueryParam("bike") int bikeID, @QueryParam("station") int stationID) {
    Rent rent = rents.lastRentForGivenBike(bikeID);
    java.util.Date date= new java.util.Date();
    rent.setEnddate(new Timestamp(date.getTime()));
    rents.saveOrUpdate(rent);
    Usser usser = ussers.get(rent.getUsser());
    usser.setBike(null);
    ussers.saveOrUpdate(usser);

    Bike bike = bikes.get(bikeID);
    bike.setStation(stationID);
    bikes.saveOrUpdate(bike);

    return Response.ok().build();
  }

  @PUT
  @Path("/{id}")
  @Consumes(MediaType.APPLICATION_JSON)
  public Response changeRentBasicData(@PathParam("id") String id, String queryBody) {
    // TODO
    return Response.ok().build();
  }

}
